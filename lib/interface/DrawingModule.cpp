#include "../../include/interface/DrawingModule.hpp"
#include <QPainter>
#include <QGraphicsItemGroup>
#include <QDebug>

DrawingModule::DrawingModule(int nSources, int nBuffers, int nDevices, StepData *initialState, QWidget *parent) : QGraphicsView(parent)
{
    this->setMinimumHeight(500);
    this->setMinimumWidth(600);

    this->scene = new QGraphicsScene();
    this->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    this->setScene(scene);

    this->drawData.push_back(initialState);

    double curr_y = SPACE_BETWEEN;
    for (int i = 0; i < nSources; i++)
    {
        QGraphicsItemGroup *line = new QGraphicsItemGroup();
        this->scene->addItem(line);
        this->linesSources.push_back(line);

        QGraphicsTextItem *tt = scene->addText(tr("Источник %1").arg(i + 1));
        line->addToGroup(tt);

        tt->setPos(10, curr_y);
        tt->setScale(1.6);

        curr_y += SPACE_BETWEEN;
    }

    for (int i = 0; i < nBuffers; i++)
    {
        QGraphicsItemGroup *line = new QGraphicsItemGroup();
        this->scene->addItem(line);
        this->linesBuffers.push_back(line);

        QGraphicsTextItem *tt = scene->addText(tr("Буфер %1").arg(i + 1));
        line->addToGroup(tt);

        tt->setPos(10, curr_y);
        tt->setScale(1.6);

        curr_y += SPACE_BETWEEN;
    }

    for (int i = 0; i < nDevices; i++)
    {
        QGraphicsItemGroup *line = new QGraphicsItemGroup();
        this->scene->addItem(line);
        this->linesDevices.push_back(line);

        QGraphicsTextItem *tt = scene->addText(tr("Прибор %1").arg(i + 1));
        line->addToGroup(tt);

        tt->setPos(10, curr_y);
        tt->setScale(1.6);

        curr_y += SPACE_BETWEEN;
    }

    // this->linesSources[2]->addToGroup(scene->addLine(150, 35 * (2 + 1), 200, 35 * (2 + 1), timeLinePen));
}

void DrawingModule::addStep(StepData *step)
{
    // TODO сделать проверку, что что-то изменилось
    StepData *prev = this->drawData.back();

    double fromX = prev->timestamp * this->TIME_TO_PIXELS + this->MIN_X;
    double toX = step->timestamp * this->TIME_TO_PIXELS + this->MIN_X;

    for (int i = 0; i < this->linesSources.size(); i++)
    {
        double currY = (i + 2) * this->SPACE_LINES - 12;

        double offsetY = ((prev->sourceData[i] != nullptr) ? -10 : 0);

        if (prev->sourceData[i] != step->sourceData[i])
        {
            this->linesSources[i]->addToGroup(
                this->scene->addLine(toX, currY, toX, currY - 10, QPen(Qt::red, 3)));
        }

        this->linesSources[i]
            ->addToGroup(this->scene->addLine(fromX, currY + offsetY, toX, currY + offsetY, QPen(Qt::red, 3)));
    }

    for (int i = 0; i < this->linesBuffers.size(); i++)
    {
        double currY = (i + 2) * this->SPACE_LINES +
                       +this->SPACE_LINES * (this->linesSources.size()) - 12;

        double offsetY = ((prev->bufferData[i] != nullptr)
                              ? -10
                              : 0);

        if (prev->bufferData[i] != step->bufferData[i])
        {
            this->linesBuffers[i]->addToGroup(
                this->scene->addLine(toX, currY, toX, currY - 10, QPen(Qt::red, 3)));
        }

        this->linesBuffers[i]->addToGroup(this->scene->addLine(fromX, currY + offsetY, toX, currY + offsetY, QPen(Qt::red, 3)));
    }

    for (int i = 0; i < this->linesDevices.size(); i++)
    {
        double currY = (i + 2) * this->SPACE_LINES +
                       +this->SPACE_LINES * (this->linesSources.size() + this->linesBuffers.size()) - 12;

        double offsetY = ((prev->deviceData[i] != nullptr)
                              ? -10
                              : 0);

        if (prev->deviceData[i] != step->deviceData[i])
        {
            this->linesDevices[i]->addToGroup(
                this->scene->addLine(toX, currY, toX, currY - 10, QPen(Qt::red, 3)));
        }

        this->linesDevices[i]->addToGroup(
            this->scene->addLine(fromX, currY + offsetY, toX, currY + offsetY, QPen(Qt::red, 3)));
    }

    this->drawData.push_back(step);
}
