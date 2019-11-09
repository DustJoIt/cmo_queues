#include "../include/SourceManager.hpp"

SourceManager::SourceManager(StatManager *manager, int sourcesAmount, double lambda)
{
    this->sources = std::vector<Source>();
    this->manager = manager;
    this->requestsDone = 0;

    for (int i = 0; i < sourcesAmount; i++)
    {
        this->sources.push_back(Source(manager, i + 1, lambda));
    }

    // Выбрать заявку с минимальным временем

    this->getNextEmitTime();
}

void SourceManager::getNextEmitTime()
{
    double minTime = this->sources[0].current->created_at;
    int indexOfSource = 0;

    for (int i = 1; i < this->sources.size(); i++)
    {
        if (this->sources[i].current->created_at < minTime)
        {
            minTime = this->sources[i].current->created_at;
            indexOfSource = i;
        }
    }

    this->nextEventTime = minTime;
    this->indexOfSourceToEmit = indexOfSource;
}

Request *SourceManager::nextEmit()
{
    Request *tmp = this->sources[this->indexOfSourceToEmit].emitRequest();
    this->getNextEmitTime();

    this->manager->requestMade(tmp);
    this->requestsDone++;
    return tmp;
}

std::vector<Request *> SourceManager::status()
{
    std::vector<Request *> toGive;
    for (int i = 0; i < this->sources.size(); i++)
    {
        toGive.push_back(this->sources[i].current);
    }

    return toGive;
}