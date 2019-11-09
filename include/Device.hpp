#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <list>
#include "StatManager.hpp"
#include "Buffer.hpp"
#include "Request.hpp"

class Device
{
private:
    int deviceNumber;
    double a;
    double b;
    double prevProcessTime;
public:
    Request *currentRequest;
    void freeDevice();
    Device(StatManager *manager, int deviceNumber, double a, double b);
    void receiveRequest(Request *request);
    bool isAvailable();
};

#endif
