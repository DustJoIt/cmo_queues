#ifndef INTERFACE_AUTO_HPP
#define INTERFACE_AUTO_HPP

#include <QWidget>
#include "../ModulingUnit.hpp"

class Auto: public QWidget
{
public:
    Auto(ModulingUnit * unit);
private:
    // Настройка с двумя кнопками -> они переходят в автоматический режим или в ручной 
};

#endif