#include "../include/BufferManager.hpp"
#include <iostream>
#include <iomanip>
#include <iterator>

BufferManager::BufferManager(StatManager *manager, int bufferNumber)
{
    this->buffers_ = std::vector<Buffer>();

    this->manager = manager;

    for (int i = 0; i < bufferNumber; i++)
    {
        this->buffers_.push_back(Buffer(manager, i));
    }

    this->currentPackage_ = std::list<Buffer *>();
    this->currentlyOnBufferNum = 0;
}

bool BufferManager::canEmitRequest()
{
    for (int i = 0; i < this->buffers_.size(); i++)
    {
        if (!buffers_[i].isAvailable())
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
    if (!this->currentPackage_.size())
    {
        this->formPackage();
    }

    Buffer *bufferToEmit = this->currentPackage_.back();
    this->currentPackage_.pop_back();

    return bufferToEmit->emitRequest();
}

void BufferManager::receiveRequest(Request *req)
{
    // Проверить на наличие свободных мест
    for (int i = 0; i < this->buffers_.size(); i++)
    {
        int actualIndex = (i + this->currentlyOnBufferNum) % this->buffers_.size();
        if (this->buffers_[actualIndex].isAvailable())
        {
            this->buffers_[actualIndex].receiveRequest(req);
            this->currentlyOnBufferNum = (actualIndex + 1) % buffers_.size();
            return;
        }
    }

    // Выбить
    for (int i = 0; i < this->buffers_.size(); i++)
    {
        int actualIndex = (i + this->currentlyOnBufferNum) % this->buffers_.size();
        if (req->source < this->buffers_[i].getBufferedRequestPriority())
        {
            this->manager->receiveFailure(this->buffers_[actualIndex].bufferedRequest_, req->created_at);
            // std::cout << "ЗАЯВКА ВЫБИТА время: " << std::setprecision(15) << req->created_at << std::endl;
            // std::cout << "Создана: " << this->buffers_[actualIndex].bufferedRequest_->created_at << std::endl;
            // std::cout << "Источник: " << this->buffers_[actualIndex].bufferedRequest_->source << std::endl;

            this->currentPackage_.remove(&(this->buffers_[actualIndex]));
            this->buffers_[actualIndex].receiveRequest(req);
            this->currentlyOnBufferNum = (actualIndex + 1) % buffers_.size();
            return;
        }
    }

    // std::cout << "ОТКАЗ время: " << std::setprecision(15) << req->created_at << std::endl;
    // std::cout << "Источник: " << req->source << std::endl;
    this->manager->receiveFailure(req, req->created_at);
};

void BufferManager::formPackage()
{
    // Пройтись, узнать максимальный приоритет
    // Пройтись в обратном порядке, взять
    int priority = this->buffers_[0].getBufferedRequestPriority();
    for (auto it = this->buffers_.begin(); it != this->buffers_.end(); it++)
    {
        priority = std::min(priority, (*it).getBufferedRequestPriority());
    }

    for (auto it = this->buffers_.rbegin(); it != this->buffers_.rend(); it++)
    {
        if ((*it).getBufferedRequestPriority() == priority)
        {
            this->currentPackage_.push_back(&(*it));
        }
    }
}

std::vector<Request *> BufferManager::status()
{
    std::vector<Request *> toGive;
    for (int i = 0; i < this->buffers_.size(); i++)
    {
        toGive.push_back(this->buffers_[i].bufferedRequest_);
    }

    return toGive;
}
