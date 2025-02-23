#include "iostream"
#include "../include/ModulingUnit.hpp"

#include <QDebug>

ModulingUnit::ModulingUnit(int nSources, int nBuffer, int nDevices, int amount, double labmda, double a, double b)
{
    srand(time(NULL));
    this->manager = new StatManager(nSources, nDevices);
    this->amount = amount;
    this->devices = new DeviceManager(this->manager, nDevices, a, b);
    this->buffers = new BufferManager(this->manager, nBuffer);
    this->sources = new SourceManager(this->manager, nSources, labmda);
    this->sourceTime = 0;
    this->deviceTime = 0;
}

void ModulingUnit::singularStep()
{
    this->sourceTime = sources->nextEventTime;
    this->deviceTime = devices->nextEventTime;

    if (this->deviceTime <= this->sourceTime)
    {
        devices->freeDevice();
        // Проверить, есть ли заявки на буффере
        if (buffers->canEmitRequest())
        {
            devices->receiveRequest(buffers->emitRequest());
        }
    }
    else
    {
        buffers->receiveRequest(sources->nextEmit());

        if (devices->canAcceptRequest())
        {
            Request *tmp = buffers->emitRequest();

            devices->receiveRequest(tmp);
        }
    }
}

void ModulingUnit::fullyModulate()
{
    while (sources->requestsDone < amount)
    {
        this->sourceTime = sources->nextEventTime;
        this->deviceTime = devices->nextEventTime;

        if (this->deviceTime <= this->sourceTime)
        {
            devices->freeDevice();
            // Проверить, есть ли заявки на буффере
            if (buffers->canEmitRequest())
            {
                devices->receiveRequest(buffers->emitRequest());
            }
        }
        else
        {
            buffers->receiveRequest(sources->nextEmit());
            if (devices->canAcceptRequest())
            {
                devices->receiveRequest(buffers->emitRequest());
            }
        }
    }
}

StepData *ModulingUnit::getStatus()
{
    return new StepData(
        this->sources->status(),
        this->buffers->status(),
        this->devices->status(),
        std::min(this->deviceTime, this->sourceTime));
}

StatsTableData *ModulingUnit::getStats()
{
    return this->manager->getStats(std::min(this->deviceTime, this->sourceTime));
}