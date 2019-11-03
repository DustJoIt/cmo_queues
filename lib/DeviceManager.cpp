#include "../include/DeviceManager.hpp"
#include <limits>

#include <QDebug>

DeviceManager::DeviceManager(StatManager *manager, int devicesAmount, double a, double b)
{
    this->devices_ = std::vector<Device>();
    this->requestsDone = 0;

    this->manager = manager;

    for (int i = 0; i < devicesAmount; i++)
    {
        this->devices_.push_back(Device(manager, i + 1, a, b));
    }

    // Выбрать заявку с минимальным временем

    this->getNextEmitTime();
}

void DeviceManager::getNextEmitTime()
{
    // Я не понимаю, как в этом языке написать reduce
    double minTime;
    if (this->devices_[0].isAvailable())
    {
        minTime = std::numeric_limits<double>::infinity();
    }
    else
    {
        minTime = this->devices_[0].currentRequest->done_in;
    }
    
    int indexOfSource = 0;

    for (int i = 1; i < this->devices_.size(); i++)
    {
        double deviceEmitTime = this->devices_[i].isAvailable()
                                    ? 9999999999
                                    : this->devices_[i].currentRequest->done_in;
        if (deviceEmitTime < minTime)
        {
            minTime = deviceEmitTime;
            indexOfSource = i;
        }
    }

    this->nextEventTime = minTime;
    this->indexOfNextFreeDevice = indexOfSource;
}

bool DeviceManager::canAcceptRequest()
{
    for (int i = 0; i < this->devices_.size(); i++)
    {
        if (devices_[i].isAvailable())
        {
            return true;
        }
    }
    return false;
}

void DeviceManager::freeDevice()
{
    // Заявка обработана
    this->requestsDone++;

    this->manager->receiveSuccess(
        this->devices_[this->indexOfNextFreeDevice].currentRequest,
        this->indexOfNextFreeDevice);

    this->devices_[this->indexOfNextFreeDevice].freeDevice();
    this->getNextEmitTime();
}

void DeviceManager::receiveRequest(Request *request)
{
    for (int i = 0; i < this->devices_.size(); i++)
    {
        if (devices_[i].isAvailable())
        {
            devices_[i].receiveRequest(request);

            this->manager->requestReceived(request);

            this->getNextEmitTime();
            return;
        }
    }
}

std::vector<Request *> DeviceManager::status()
{
    std::vector<Request *> toGive;
    for (int i = 0; i < this->devices_.size(); i++)
    {
        toGive.push_back(this->devices_[i].currentRequest);
    }

    return toGive;
}