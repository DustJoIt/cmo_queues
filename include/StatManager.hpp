#if !defined(CMO_STAT_MANAGER)
#define CMO_STAT_MANAGER

#include <vector>

#include "./Request.hpp"

struct StatsPerSource
{
    int numberOfGeneratedRequests;
    int numberOfFailures;
    int numberOfSuccesses;
    double timeBeing;

    double timeWaiting;
    double squaredTimeWaiting;

    double timeProcessing;
    double squaredTimeProcessing;

public:
    StatsPerSource();
    int getN();
    double getFailureProb();
    double avgTimeBeing();
    double avgTimeWaiting();
    double avgTimeProcessing();
    double dispTimeWaiting();
    double dispTimeProcessing();
    double getK(double time);

    void requestMade();
    void requestReceived(Request *req);
    void receiveSuccess(Request *req);
    void receiveFailure(Request *req, double time);
};

struct StatsTableData
{
    std::vector<int> N;
    std::vector<double> failureProb;
    std::vector<double> avgTimeBeing;
    std::vector<double> avgTimeWaiting;
    std::vector<double> avgTimeProccessing;
    std::vector<double> dispTimeBeing;
    std::vector<double> dispTimeProccessing;
    std::vector<double> K;
};

class StatManager
{
private:
    std::vector<StatsPerSource> stats;
    std::vector<double> deviceTimeWork;

public:
    StatManager(int nSources, int nDevices);
    void requestMade(Request *req);
    void requestReceived(Request *req);
    void receiveSuccess(Request *req, int deviceNum);
    void receiveFailure(Request *req, double time);
    StatsTableData *getStats(double time);
};

#endif // CMO_STAT_MANAGER
