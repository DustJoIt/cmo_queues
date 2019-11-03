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
    QApplication app(argc, argv);

    Interface vv;

    vv.show();
    return app.exec();
}
