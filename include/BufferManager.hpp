#if !defined(CMO_BUFFER_MANAGER_HPP)
#define CMO_BUFFER_MANAGER_HPP

#include "StatManager.hpp"
#include "Request.hpp"
#include "Buffer.hpp"
#include <vector>
#include <list>

class BufferManager
{
private:
    std::vector<Buffer> buffers;
    int currentlyOnBufferNum;
    std::list<Buffer *> currentPackage;
    StatManager *manager;

    void formPackage();

public:
    std::vector<Request *> status();
    BufferManager(StatManager *manager, int bufferNumber);
    void receiveRequest(Request *req);
    bool canEmitRequest();
    Request *emitRequest();
};

#endif // CMO_BUFFER_MANAGER_HPP
