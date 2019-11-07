#if !defined(DRAWING_MODULE_HPP)
#define DRAWING_MODULE_HPP

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <vector>
#include <string>
#include "../Request.hpp"

class DrawingModule : public QGraphicsView
{
public:
    DrawingModule(int nSources, int nBuffers, int nDevices, StepData *initialState, QWidget *parent = 0);
    QGraphicsScene *scene;
    std::vector<QGraphicsItemGroup *> linesSources;
    std::vector<QGraphicsItemGroup *> linesBuffers;
    std::vector<QGraphicsItemGroup *> linesDevices;
    QGraphicsItemGroup *lineReject;

    const int SPACE_BETWEEN = 38;
    const int MIN_X = 150;
    const double SPACE_LINES = 38;
    const double TOP_LINE = 9;

    const double TIME_TO_PIXELS = 1000;

    void addStep(StepData *step);

private:
    StepData *prev = nullptr;
    inline QGraphicsLineItem *addLine(double fromX, double fromY, double toX, double toY);
    QGraphicsTextItem *addSignature(double x, double y, int source, int num);
    void makeStepLines(
        std::vector<QGraphicsItemGroup *> &lines,
        std::vector<Request *> &prev,
        std::vector<Request *> &curr,
        double fromX,
        double &fromY,
        double toX);
    void makeLines(int N, double &initial_y, std::vector<QGraphicsItemGroup *> &lineHolder, std::string const &name);
    // void drawStep(StepData &prev, StepData &curr);
};

#endif // DRAWING_MODULE_HPP
