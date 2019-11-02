#ifndef INTERFACE_MANUAL_HPP
#define INTERFACE_MANUAL_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "../ModulingUnit.hpp"
#include "DrawingModule.hpp"

class Manual : public QWidget
{
public:
    Manual(int nSources, int nBuffer, int nDevices, ModulingUnit *unit);

private:
    void check();
    QPushButton *button;
    DrawingModule *yey;
    ModulingUnit *unit;
};

#endif