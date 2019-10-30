#include "iostream"

#include "./include/interface/Interface.hpp"

const int NUM_BUFFERS = 3;
const int NUM_DEVICES = 3;
const int NUM_SOURCES = 10;
const int NUM_REQUESTS_TO_BE_DONE = 10000;

#include <QApplication>
#include <QWidget>
#include <QLabel>

int main(int argc, char **argv)
{
    // srand(time(NULL));
    // StatManager stats = StatManager(NUM_SOURCES, NUM_DEVICES);
    // DeviceManager devices = DeviceManager(&stats, NUM_DEVICES);
    // BufferManager buffers = BufferManager(&stats, NUM_BUFFERS);
    // SourceManager sources = SourceManager(&stats, NUM_SOURCES);

    // double sourceTime;
    // double deviceTime;

    // while (devices.requestsDone < NUM_REQUESTS_TO_BE_DONE)
    // {
    //     sourceTime = sources.nextEventTime;
    //     deviceTime = devices.nextEventTime;

    //     if (deviceTime <= sourceTime)
    //     {
    //         devices.freeDevice();
    //         // Проверить, есть ли заявки на буффере
    //         if (buffers.canEmitRequest())
    //         {
    //             devices.receiveRequest(buffers.emitRequest());
    //         }
    //     }
    //     else
    //     {
    //         buffers.receiveRequest(sources.nextEmit());
    //         if (devices.canAcceptRequest())
    //         {
    //             devices.receiveRequest(buffers.emitRequest());
    //         }
    //     }
    // }

    // stats.getN();
    // stats.getFailureProb();
    // stats.avgTimeBeing();
    // stats.avgTimeWaiting();
    // stats.avgTimeProcessing();
    // stats.dispTimeWaiting();
    // stats.dispTimeProcessing();
    // stats.getK(std::max(sourceTime, deviceTime));

    // return 0;

    QApplication app(argc, argv);

    Interface vv;

    vv.show();
    return app.exec();
}
