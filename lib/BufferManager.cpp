#include "../include/BufferManager.hpp"
#include <iostream>
#include <iomanip>
#include <iterator>

BufferManager::BufferManager(StatManager *manager, int bufferNumber)
{
    this->buffers = std::vector<Buffer>();

    this->manager = manager;

    for (int i = 0; i < bufferNumber; i++)
    {
        this->buffers.push_back(Buffer(manager, i));
    }

    this->currentPackage = std::list<Buffer *>();
    this->currentlyOnBufferNum = 0;
}

bool BufferManager::canEmitRequest()
{
    for (int i = 0; i < this->buffers.size(); i++)
    {
        if (!buffers[i].isAvailable())
        {
            return true;
        };
    }
    return false;
}

Request *BufferManager::emitRequest()
{
    // Проверить пакет
    // Если нет пакета, сформировать
    if (!this->currentPackage.size())
    {
        this->formPackage();
    }

    Buffer *bufferToEmit = this->currentPackage.back();
    this->currentPackage.pop_back();

    return bufferToEmit->emitRequest();
}

void BufferManager::receiveRequest(Request *req)
{
    // Проверить на наличие свободных мест
    for (int i = 0; i < this->buffers.size(); i++)
    {
        int actualIndex = (i + this->currentlyOnBufferNum) % this->buffers.size();
        if (this->buffers[actualIndex].isAvailable())
        {
            this->buffers[actualIndex].receiveRequest(req);
            this->currentlyOnBufferNum = (actualIndex + 1) % buffers.size();
            return;
        }
    }

    // Выбить
    for (int i = 0; i < this->buffers.size(); i++)
    {
        int actualIndex = (i + this->currentlyOnBufferNum) % this->buffers.size();
        if (req->source < this->buffers[actualIndex].getBufferedRequestPriority())
        {
            this->manager->receiveFailure(this->buffers[actualIndex].bufferedRequest, req->created_at);

            this->currentPackage.remove(&(this->buffers[actualIndex]));
            this->buffers[actualIndex].receiveRequest(req);
            this->currentlyOnBufferNum = (actualIndex + 1) % buffers.size();
            return;
        }
    }

    this->manager->receiveFailure(req, req->created_at);
};

void BufferManager::formPackage()
{
    // Пройтись, узнать максимальный приоритет
    // Пройтись в обратном порядке, взять
    int priority = this->buffers[0].getBufferedRequestPriority();
    for (auto it = this->buffers.begin(); it != this->buffers.end(); it++)
    {
        priority = std::min(priority, (*it).getBufferedRequestPriority());
    }

    for (auto it = this->buffers.rbegin(); it != this->buffers.rend(); it++)
    {
        if ((*it).getBufferedRequestPriority() == priority)
        {
            this->currentPackage.push_back(&(*it));
        }
    }

    this->currentPackage.sort([](Buffer *a, Buffer *b) {
        return a->bufferedRequest->created_at > b->bufferedRequest->created_at;
    });
}

std::vector<Request *> BufferManager::status()
{
    std::vector<Request *> toGive;
    for (int i = 0; i < this->buffers.size(); i++)
    {
        toGive.push_back(this->buffers[i].bufferedRequest);
    }

    return toGive;
}
