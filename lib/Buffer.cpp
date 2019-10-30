#include "../include/Buffer.hpp"
#include <limits>

Buffer::Buffer(StatManager *manager, int bufferNumber)
{
    this->bufferNumber_ = bufferNumber;
    this->bufferedRequest_ = nullptr;
}

bool Buffer::isAvailable()
{
    return (this->bufferedRequest_ == nullptr);
}

void Buffer::receiveRequest(Request *request)
{
    this->bufferedRequest_ = request;
}

Request *Buffer::emitRequest()
{
    Request *tmp = this->bufferedRequest_;
    this->bufferedRequest_ = nullptr;
    return tmp;
}

int Buffer::getBufferedRequestPriority() {
    return this->isAvailable() ? std::numeric_limits<int>::max() : this->bufferedRequest_->source;
}