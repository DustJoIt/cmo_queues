#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include "./Manual.hpp"

class Interface : public QWidget
{
public:
    Interface();

private:
    QWidget *buttonsHolder;
    QPushButton *buttons[2];

    QGroupBox *formGroupBox;
    QLineEdit *lineEdits[7];

    void initializeButtons();
    void initializeFormLines();

    void startModuling(bool mode);
    // Настройка с двумя кнопками -> они переходят в автоматический режим или в ручной
};

#endif