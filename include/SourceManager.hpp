#if !defined(CMO_SOURCE_MANAGER_HPP)
#define CMO_SOURCE_MANAGER_HPP

#include "StatManager.hpp"
#include "Source.hpp"
#include <vector>

class SourceManager
{
private:
    std::vector<Source> sources_;
    int indexOfSourceToEmit;
    void getNextEmitTime();
    StatManager *manager;

public:
    double nextEventTime;
    int requestsDone;
    std::vector<Request *> status();
    SourceManager(StatManager *manager, int sourcesAmount, double labmda);
    Request *nextEmit();
};

#endif // CMO_SOURCE_MANAGER_HPP
