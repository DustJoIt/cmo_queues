#include "../include/Device.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <QDebug>

Device::Device(StatManager *manager, int deviceNumber, double a, double b)
{
    this->deviceNumber = deviceNumber;
    this->prevProcessTime = 0;
    this->a = a;
    this->currentRequest = nullptr;
    this->b = b;
}

bool Device::isAvailable()
{
    return (this->currentRequest == nullptr);
}

void Device::receiveRequest(Request *request)
{
    double processTime = (this->b - this->a) * ((double)rand() / RAND_MAX) + this->a;

    if (this->prevProcessTime > request->created_at)
    {
        // Т.е. девайс освободился, принял с буффера
        request->done_in = prevProcessTime + processTime;
        request->received_in = prevProcessTime;
    }
    else
    {
        // Т.е. не стоял на буфферах
        request->done_in = request->created_at + processTime;
        request->received_in = request->created_at;
    }

    this->currentRequest = request;
}

void Device::freeDevice()
{
    // Вызов метода, когда освободился прибор
    this->prevProcessTime = this->currentRequest->done_in;
    this->currentRequest = nullptr;
}