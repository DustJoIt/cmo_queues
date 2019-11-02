#include "../include/Source.hpp"
#include <cmath>

Source::Source(StatManager *manager, int sourceNumber, double lambda)
{
    this->sourceNumber_ = sourceNumber;
    this->lambda_ = lambda;
    this->currNum_ = 0;
    this->current = nullptr;
    this->generateRequest();
};

Request *Source::emitRequest()
{
    Request *tmp = this->current;
    this->generateRequest();
    return tmp;
};

void Source::generateRequest()
{
    double addedTime = (-1 / (this->lambda_)) * log((double)rand() / RAND_MAX);
    double prevTime = this->current == nullptr ? 0 : this->current->created_at;
    this->current = new Request(prevTime + addedTime, this->sourceNumber_, ++this->currNum_);
}