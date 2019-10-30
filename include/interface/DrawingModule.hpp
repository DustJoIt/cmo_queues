#if !defined(DRAWING_MODULE_HPP)
#define DRAWING_MODULE_HPP

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <vector>
#include "../Request.hpp"

class DrawingModule : public QGraphicsView
{
public:
    DrawingModule(int nSources, int nBuffers, int nDevices, StepData * initialState, QWidget *parent = 0);
    QGraphicsScene *scene;
    std::vector<QGraphicsItemGroup *> linesSources;
    std::vector<QGraphicsItemGroup *> linesBuffers;
    std::vector<QGraphicsItemGroup *> linesDevices;

    const int SPACE_BETWEEN = 38;
    const int MIN_X = 150;
    const double SPACE_LINES = 38;
    const double TOP_LINE = 9;

    const double TIME_TO_PIXELS = 1000;

    void addStep(StepData *step);

private:
    std::vector<StepData *> drawData;
    // void drawStep(StepData &prev, StepData &curr);
};

#endif // DRAWING_MODULE_HPP
