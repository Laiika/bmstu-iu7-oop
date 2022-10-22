#ifndef DRAW_RESULT_H
#define DRAW_RESULT_H

#include <QGraphicsScene>

#include "ui_mainwindow.h"
#include "points.h"
#include "pairs.h"

struct canvas
{
    QGraphicsScene *scene;
    double width;
    double height;
};
typedef struct canvas canvas_t;

void draw_figure(const points_t &points, const pairs_t &pairs, const canvas_t &canvas);

#endif // DRAW_RESULT_H
