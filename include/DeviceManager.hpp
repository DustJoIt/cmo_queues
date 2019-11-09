#if !defined(CMO_DEVICE_MANAGER_HPP)
#define CMO_DEVICE_MANAGER_HPP

#include "StatManager.hpp"
#include "Device.hpp"
#include <vector>

class DeviceManager
{
private:
    std::vector<Device> devices;
    int indexOfNextFreeDevice;
    void getNextEmitTime();
    StatManager *manager;

public:
    void freeDevice();
    std::vector<Request *> status();
    double nextEventTime;
    bool canAcceptRequest();
    DeviceManager(StatManager *manager, int devicesAmount, double a, double b);
    void receiveRequest(Request *request);
};

#endif // CMO_DEVICE_MANAGER_HPP
