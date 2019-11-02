#include "../../include/interface/Interface.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "../../include/ModulingUnit.hpp"
#include <QDebug>

Interface::Interface()
{
    this->initializeButtons();
    this->initializeFormLines();

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(this->formGroupBox);
    layout->addWidget(this->buttonsHolder);

    this->setLayout(layout);
}

void Interface::initializeButtons()
{
    this->buttonsHolder = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    buttons[0] = new QPushButton(tr("Ручной"));
    layout->addWidget(buttons[0]);
    connect(buttons[0], &QPushButton::clicked, this, [this]() { this->startModuling(true); });

    buttons[1] = new QPushButton(tr("Автоматический"));
    layout->addWidget(buttons[1]);
    
    buttonsHolder->setLayout(layout);
}

void Interface::initializeFormLines()
{
    this->formGroupBox = new QGroupBox(tr("Настройки"));
    QFormLayout *layout = new QFormLayout;

    this->lineEdits[0] = new QLineEdit(tr("3"));
    this->lineEdits[1] = new QLineEdit(tr("3"));
    this->lineEdits[2] = new QLineEdit(tr("3"));
    this->lineEdits[3] = new QLineEdit(tr("10000"));
    this->lineEdits[4] = new QLineEdit(tr("3"));
    this->lineEdits[5] = new QLineEdit(tr("0"));
    this->lineEdits[6] = new QLineEdit(tr("1"));

    layout->addRow(new QLabel(tr("Количество источников:")), this->lineEdits[0]);
    layout->addRow(new QLabel(tr("Количество буферов:")), this->lineEdits[1]);
    layout->addRow(new QLabel(tr("Количество приборов:")), this->lineEdits[2]);
    layout->addRow(new QLabel(tr("Количество заявок:")), this->lineEdits[3]);
    layout->addRow(new QLabel(tr("Интенсивность источников:")), this->lineEdits[4]);
    layout->addRow(new QLabel(tr("Приборы, A:")), this->lineEdits[5]);
    layout->addRow(new QLabel(tr("Приборы, B:")), this->lineEdits[6]);

    this->formGroupBox->setLayout(layout);
}

void Interface::startModuling(bool mode)
{
    int nSources = this->lineEdits[0]->text().toInt();
    int nBuffer = this->lineEdits[1]->text().toInt();
    int nDevices = this->lineEdits[2]->text().toInt();
    int amount = this->lineEdits[3]->text().toInt();
    double labmda = this->lineEdits[4]->text().toDouble();
    double a = this->lineEdits[5]->text().toDouble();
    double b = this->lineEdits[6]->text().toDouble();
    ModulingUnit *unit = new ModulingUnit(nSources, nBuffer, nDevices, amount, labmda, a, b);

    // TODO Auto or Manual;
    QWidget *goTo = new Manual(nSources, nBuffer, nDevices, unit);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(goTo);

    qDeleteAll(this->children());
    delete this->layout();

    this->setLayout(layout);
}