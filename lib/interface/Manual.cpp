#include "../../include/interface/Manual.hpp"
#include <QGridLayout>
#include <QDebug>

Manual::Manual(int nSources, int nBuffer, int nDevices, ModulingUnit *unit)
{
    this->unit = unit;
    this->yey = new DrawingModule(nSources, nBuffer, nDevices, this->unit->getStatus());
    this->button = new QPushButton(tr("Сделать шаг"));

    QGridLayout *mainLayout = new QGridLayout();

    mainLayout->addWidget(yey);
    mainLayout->addWidget(this->button);

    connect(this->button,
            &QPushButton::clicked, this, &Manual::check);

    this->setLayout(mainLayout);
}

void Manual::check()
{
    this->unit->singularStep();
    this->yey->addStep(this->unit->getStatus());
}