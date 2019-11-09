#include "../include/Buffer.hpp"
#include <limits>

Buffer::Buffer(StatManager *manager, int bufferNumber)
{
    this->bufferNumber = bufferNumber;
    this->bufferedRequest = nullptr;
}

bool Buffer::isAvailable()
{
    return (this->bufferedRequest == nullptr);
}

void Buffer::receiveRequest(Request *request)
{
    this->bufferedRequest = request;
}

Request *Buffer::emitRequest()
{
    Request *tmp = this->bufferedRequest;
    this->bufferedRequest = nullptr;
    return tmp;
}

int Buffer::getBufferedRequestPriority() {
    return this->isAvailable() ? std::numeric_limits<int>::max() : this->bufferedRequest->source;
}