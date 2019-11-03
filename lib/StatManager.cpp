#include <algorithm>

#include "../include/StatManager.hpp"

StatsPerSource::StatsPerSource()
{
    this->numberOfGeneratedRequests = 0;
    this->numberOfFailures = 0;
    this->numberOfSuccesses = 0;

    this->timeBeing = 0;

    this->timeWaiting = 0;
    this->squaredTimeWaiting = 0;

    this->timeProcessing = 0;
    this->squaredTimeProcessing = 0;
}

int StatsPerSource::getN()
{
    return this->numberOfGeneratedRequests;
}

double StatsPerSource::getFailureProb()
{
    return (double)this->numberOfFailures / this->numberOfGeneratedRequests;
}

double StatsPerSource::avgTimeBeing()
{
    return this->timeBeing / this->numberOfGeneratedRequests;
}

double StatsPerSource::avgTimeWaiting()
{
    return this->timeWaiting / this->numberOfSuccesses;
}

double StatsPerSource::avgTimeProcessing()
{
    return this->timeProcessing / this->numberOfSuccesses;
}

double StatsPerSource::dispTimeWaiting()
{
    return (this->squaredTimeWaiting / this->numberOfSuccesses) -
           (this->avgTimeWaiting() * this->avgTimeWaiting());
}
double StatsPerSource::dispTimeProcessing()
{
    return (this->squaredTimeProcessing / this->numberOfSuccesses) -
           (this->avgTimeProcessing() * this->avgTimeProcessing());
}
double StatsPerSource::getK(double time)
{
    return (this->timeProcessing / time);
}

void StatsPerSource::receiveSuccess(Request *req)
{
    this->numberOfSuccesses++;

    this->timeProcessing += req->done_in - req->received_in;
    this->squaredTimeProcessing += (req->done_in - req->received_in) * (req->done_in - req->received_in);

    this->timeBeing += req->done_in - req->created_at;
}

void StatsPerSource::receiveFailure(Request *req, double time)
{
    this->numberOfFailures++;

    this->timeBeing += time - req->created_at;
}

void StatsPerSource::requestMade()
{
    this->numberOfGeneratedRequests++;
}

void StatsPerSource::requestReceived(Request *req)
{
    this->timeWaiting += req->received_in - req->created_at;
    this->squaredTimeWaiting += (req->received_in - req->created_at) * (req->received_in - req->created_at);
}

StatManager::StatManager(int nSources, int nDevices)
{
    this->deviceTimeWork = std::vector<double>(nDevices, 0);
    for (int i = 0; i < nSources; i++)
    {
        this->stats.push_back(StatsPerSource());
    }
}

void StatManager::requestMade(Request *req)
{
    this->stats[req->source - 1].requestMade();
}

void StatManager::requestReceived(Request *req)
{
    this->stats[req->source - 1].requestReceived(req);
}

void StatManager::receiveSuccess(Request *req, int deviceNum)
{
    this->stats[req->source - 1].receiveSuccess(req);

    this->deviceTimeWork[deviceNum] += req->done_in - req->received_in;
}

void StatManager::receiveFailure(Request *req, double time)
{
    this->stats[req->source - 1].receiveFailure(req, time);
}

StatsTableData *StatManager::getStats(double time)
{
    StatsTableData *toGive = new StatsTableData();
    for (int i = 0; i < this->stats.size(); i++)
    {
        StatsPerSource tmp = this->stats[i];
        toGive->N.push_back(tmp.getN());
        toGive->failureProb.push_back(tmp.getFailureProb());
        toGive->avgTimeBeing.push_back(tmp.avgTimeBeing());
        toGive->avgTimeWaiting.push_back(tmp.avgTimeWaiting());
        toGive->avgTimeProccessing.push_back(tmp.avgTimeProcessing());
        toGive->dispTimeBeing.push_back(tmp.dispTimeWaiting());
        toGive->dispTimeProccessing.push_back(tmp.dispTimeProcessing());
    }

    for (int i = 0; i < this->deviceTimeWork.size(); i++)
    {
        toGive->K.push_back(this->deviceTimeWork[i] / time);
    }

    return toGive;
}
