#ifndef INTERFACE_MANUAL_HPP
#define INTERFACE_MANUAL_HPP

#include <QWidget>
#include <QPushButton>
#include "../ModulingUnit.hpp"
#include "DrawingModule.hpp"

class Manual : public QWidget
{
public:
    Manual(int nSources, int nBuffer, int nDevices, ModulingUnit *unit);

private:

    void check();
    QPushButton *buttons[2];
    DrawingModule *yey;
    ModulingUnit *unit;
};

#endif