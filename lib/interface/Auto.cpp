#include "../../include/interface/Auto.hpp"
#include <QGridLayout>

Auto::Auto(int nSources, int nDevices, ModulingUnit *unit)
{
    this->unit = unit;
    unit->fullyModulate();
    StatsTableData *table = unit->getStats();
    QGridLayout *mainLayout = new QGridLayout();

    // Основная таблица
    this->tables[0] = new QTableWidget(nSources, 7);
    for (int i = 0; i < nSources; i++)
    {
        this->tables[0]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg(table->N[i])));
        this->tables[0]->setItem(i, 1, new QTableWidgetItem(tr("%1").arg(table->failureProb[i])));
        this->tables[0]->setItem(i, 2, new QTableWidgetItem(tr("%1").arg(table->avgTimeBeing[i])));
        this->tables[0]->setItem(i, 3, new QTableWidgetItem(tr("%1").arg(table->avgTimeWaiting[i])));
        this->tables[0]->setItem(i, 4, new QTableWidgetItem(tr("%1").arg(table->avgTimeProccessing[i])));
        this->tables[0]->setItem(i, 5, new QTableWidgetItem(tr("%1").arg(table->dispTimeBeing[i])));
        this->tables[0]->setItem(i, 6, new QTableWidgetItem(tr("%1").arg(table->dispTimeProccessing[i])));
    }
    this->tables[0]->setHorizontalHeaderLabels(
        QStringList() << "Кол-во заявок"
                      << "Шанс отказа"
                      << "Среднее время пребывания"
                      << "Среднее время ожидания"
                      << "Среднее время обработки"
                      << "Дисперсия времени ожидания"
                      << "Дисперсия времени обработки");
    mainLayout->addWidget(this->tables[0]);

    // Вторая таблица
    this->tables[1] = new QTableWidget(nDevices, 1);
    for (int i = 0; i < nDevices; i++)
    {
        this->tables[1]->setItem(i, 0, new QTableWidgetItem(tr("%1").arg(table->K[i])));
    } 
    this->tables[1]->setHorizontalHeaderLabels(QStringList() << "Коэф К");
    
    mainLayout->addWidget(this->tables[1]);

    this->setLayout(mainLayout);
}