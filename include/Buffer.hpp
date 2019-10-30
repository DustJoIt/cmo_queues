#if !defined(CMO_BUFFER_HPP)
#define CMO_BUFFER_HPP

#include "StatManager.hpp"
#include "Request.hpp"

class Buffer
{
private:
    int bufferNumber_;

public:
    Request *bufferedRequest_;
    Buffer(StatManager *manager, int bufferNumber);
    bool isAvailable();
    void receiveRequest(Request *request);
    Request *emitRequest();
    int getBufferedRequestPriority();
};

#endif // CMO_BUFFER_HPP
