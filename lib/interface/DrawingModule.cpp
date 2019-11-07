#include "../../include/interface/DrawingModule.hpp"
#include <QPainter>
#include <QGraphicsItemGroup>
#include <QDebug>
#include <algorithm>

void DrawingModule::makeLines(int N, double &initial_y, std::vector<QGraphicsItemGroup *> &lineHolder, std::string const &name)
{
    for (int i = 0; i < N; i++)
    {
        QGraphicsItemGroup *line = new QGraphicsItemGroup();
        this->scene->addItem(line);
        lineHolder.push_back(line);

        QGraphicsTextItem *tt = scene->addText(tr((name + " %1").c_str()).arg(i + 1));
        line->addToGroup(tt);

        tt->setPos(10, initial_y);
        tt->setScale(1.6);

        initial_y += SPACE_BETWEEN;
    }
}

inline QGraphicsLineItem *DrawingModule::addLine(double fromX, double fromY, double toX, double toY)
{
    return this->scene->addLine(fromX, fromY, toX, toY, QPen(Qt::red, 3));
}

QGraphicsTextItem *DrawingModule::addSignature(double x, double y, int source, int num)
{
    QGraphicsTextItem *tt = this->scene->addText(
        tr("%1.%2").arg(source).arg(num));
    tt->setPos(x, y);
    return tt;
}

void DrawingModule::makeStepLines(
    std::vector<QGraphicsItemGroup *> &lines,
    std::vector<Request *> &prev,
    std::vector<Request *> &curr,
    double fromX,
    double &fromY,
    double toX)
{
    // fromY - нижняя граница линии. lowMode -  подымаем вверх при наличии заявки
    for (int i = 0; i < lines.size(); i++)
    {
        double offsetY = ((prev[i] != nullptr)
                              ? -10
                              : 0);

        if (prev[i] != curr[i])
        {
            lines[i]->addToGroup(
                this->addLine(toX, fromY, toX, fromY - 10));

            if (curr[i] != nullptr)
            {
                lines[i]->addToGroup(
                    this->addSignature(
                        toX,
                        fromY - 35,
                        curr[i]->source,
                        curr[i]->num));
            }
        }

        lines[i]->addToGroup(
            this->addLine(fromX, fromY + offsetY, toX, fromY + offsetY));

        fromY += this->SPACE_LINES;
    }
}

DrawingModule::DrawingModule(int nSources, int nBuffers, int nDevices, StepData *initialState, QWidget *parent) : QGraphicsView(parent)
{
    this->setMinimumHeight(500);
    this->setMinimumWidth(600);

    this->scene = new QGraphicsScene();
    this->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    this->setScene(scene);

    this->prev = new StepData(
        std::vector<Request *>(nSources, nullptr),
        std::vector<Request *>(nBuffers, nullptr),
        std::vector<Request *>(nDevices, nullptr),
        0);

    double curr_y = SPACE_BETWEEN;

    this->makeLines(nSources, curr_y, this->linesSources, "Источник");
    this->makeLines(nBuffers, curr_y, this->linesBuffers, "Буффер");
    this->makeLines(nDevices, curr_y, this->linesDevices, "Приборы");

    // Отказ
    this->lineReject = new QGraphicsItemGroup();
    this->scene->addItem(lineReject);

    QGraphicsTextItem *tt = scene->addText(tr("Отказ"));
    this->lineReject->addToGroup(tt);

    tt->setPos(10, curr_y);
    tt->setScale(1.6);

    this->addStep(initialState);
}

void DrawingModule::addStep(StepData *step)
{
    double fromX = prev->timestamp * this->TIME_TO_PIXELS + this->MIN_X;
    double toX = step->timestamp * this->TIME_TO_PIXELS + this->MIN_X;

    double currY = 2 * this->SPACE_LINES - 12;

    this->makeStepLines(
        this->linesSources,
        prev->sourceData,
        step->sourceData,
        fromX,
        currY,
        toX);

    this->makeStepLines(
        this->linesBuffers,
        prev->bufferData,
        step->bufferData,
        fromX,
        currY,
        toX);

    this->makeStepLines(
        this->linesDevices,
        prev->deviceData,
        step->deviceData,
        fromX,
        currY,
        toX);

    this->lineReject->addToGroup(
        this->addLine(
            fromX, currY, toX, currY));

    for (int i = 0; i < this->linesSources.size(); i++)
    {
        if (
            prev->sourceData[i] != nullptr && prev->sourceData[i] != step->sourceData[i])
        {
            bool isFound = std::find(step->bufferData.begin(),
                                     step->bufferData.end(),
                                     prev->sourceData[i]) != step->bufferData.end();

            isFound = isFound || std::find(step->deviceData.begin(),
                                           step->deviceData.end(),
                                           prev->sourceData[i]) != step->deviceData.end();

            if (!isFound)
            {
                this->lineReject->addToGroup(
                    this->addLine(
                        toX, currY, toX, currY - 10));

                this->lineReject->addToGroup(
                    this->addSignature(
                        toX,
                        currY - 35,
                        prev->sourceData[i]->source,
                        prev->sourceData[i]->num));
            }
        }
    }

    for (int i = 0; i < this->linesBuffers.size(); i++)
    {
        if (
            prev->bufferData[i] != nullptr && prev->bufferData[i] != step->bufferData[i])
        {
            bool isFound = std::find(step->deviceData.begin(),
                                     step->deviceData.end(),
                                     prev->bufferData[i]) != step->deviceData.end();

            if (!isFound)
            {
                this->lineReject->addToGroup(
                    this->addLine(
                        toX, currY, toX, currY - 10));

                this->lineReject->addToGroup(
                    this->addSignature(
                        toX,
                        currY - 35,
                        prev->bufferData[i]->source,
                        prev->bufferData[i]->num));
            }
        }
    }

    delete this->prev;
    this->prev = step;
}
