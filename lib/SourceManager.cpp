#include "../include/SourceManager.hpp"

SourceManager::SourceManager(StatManager *manager, int sourcesAmount, double lambda)
{
    this->sources_ = std::vector<Source>();
    this->manager = manager;

    for (int i = 0; i < sourcesAmount; i++)
    {
        this->sources_.push_back(Source(manager, i + 1, lambda));
    }

    // Выбрать заявку с минимальным временем

    this->getNextEmitTime();
}

void SourceManager::getNextEmitTime()
{
    // Я не понимаю, как в этом языке написать reduce
    double minTime = this->sources_[0].current->created_at;
    int indexOfSource = 0;

    for (int i = 1; i < this->sources_.size(); i++)
    {
        if (this->sources_[i].current->created_at < minTime)
        {
            minTime = this->sources_[i].current->created_at;
            indexOfSource = i;
        }
    }

    this->nextEventTime = minTime;
    this->indexOfSourceToEmit = indexOfSource;
}

Request *SourceManager::nextEmit()
{
    Request *tmp = this->sources_[this->indexOfSourceToEmit].emitRequest();
    this->getNextEmitTime();

    this->manager->requestMade(tmp);
    return tmp;
}

std::vector<Request *> SourceManager::status()
{
    std::vector<Request *> toGive;
    for (int i = 0; i < this->sources_.size(); i++)
    {
        toGive.push_back(this->sources_[i].current);
    }

    return toGive;
}