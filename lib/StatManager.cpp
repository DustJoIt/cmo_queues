#include <algorithm>
#include <iostream>

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

    // delete req;
}

void StatsPerSource::receiveFailure(Request *req, double time)
{
    this->numberOfFailures++;

    this->timeBeing += time - req->created_at;

    // delete req;
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

void StatManager::getN()
{
    for (int i = 0; i < this->stats.size(); i++)
    {
        StatsPerSource stat = this->stats[i];

        std::cout << "Источник: " << i << ", сгенерировано заявок - " << stat.getN() << std::endl;
    }
}

void StatManager::getFailureProb()
{
    for (int i = 0; i < this->stats.size(); i++)
    {
        StatsPerSource stat = this->stats[i];

        std::cout << "Источник: " << i << ", шанс отказа - " << stat.getFailureProb() << std::endl;
    }
}
void StatManager::avgTimeBeing()
{
    for (int i = 0; i < this->stats.size(); i++)
    {
        StatsPerSource stat = this->stats[i];

        std::cout << "Источник: " << i << ", среднее время пребывания - " << stat.avgTimeBeing() << std::endl;
    }
}

void StatManager::avgTimeWaiting()
{
    for (int i = 0; i < this->stats.size(); i++)
    {
        StatsPerSource stat = this->stats[i];

        std::cout << "Источник: " << i << ", среднее время ожидания - " << stat.avgTimeWaiting() << std::endl;
    }
}
void StatManager::avgTimeProcessing()
{
    for (int i = 0; i < this->stats.size(); i++)
    {
        StatsPerSource stat = this->stats[i];

        std::cout << "Источник: " << i << ", среднее время обработки - " << stat.avgTimeProcessing() << std::endl;
    }
}

void StatManager::dispTimeWaiting()
{
    for (int i = 0; i < this->stats.size(); i++)
    {
        StatsPerSource stat = this->stats[i];

        std::cout << "Источник: " << i << ", дисперсия времени ожидания - " << stat.dispTimeWaiting() << std::endl;
    }
}
void StatManager::dispTimeProcessing()
{
    for (int i = 0; i < this->stats.size(); i++)
    {
        StatsPerSource stat = this->stats[i];

        std::cout << "Источник: " << i << ", дисперсия времени обработки - " << stat.dispTimeProcessing() << std::endl;
    }
}

void StatManager::getK(double time)
{
    // Переделать - здесь только Source, должны быть по Device (сейчас это работает, т.к. 3=3)
    for (int i = 0; i < this->deviceTimeWork.size(); i++)
    {
        std::cout << "Источник: " << i
                  << ", коэффициент использования устройства - "
                  << this->deviceTimeWork[i] / time << std::endl;
    }
}
