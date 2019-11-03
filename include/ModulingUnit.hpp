#if !defined(MODULING_UNIT)
#define MODULING_UNIT

#include "StatManager.hpp"
#include "BufferManager.hpp"
#include "SourceManager.hpp"
#include "DeviceManager.hpp"

class ModulingUnit
{
private:
    double sourceTime;
    double deviceTime;
    bool mode;
    int amount;
    StatManager *manager;

    DeviceManager *devices;
    BufferManager *buffers;
    SourceManager *sources;

public:
    ModulingUnit(int nSources, int nBuffer, int nDevices, int amount, double labmda, double a, double b);
    StepData *getStatus();
    void singularStep();
    StatsTableData *getStats();
    void fullyModulate();
};

#endif // MODULING_UNIT
