#include "iostream"

#include "./include/interface/Interface.hpp"
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
