#ifndef CANVAS_H
#define CANVAS_H

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

void canvas_clear(const canvas_t &canvas);
void draw_lines(const points_t &points, const pairs_t &pairs, const canvas_t &canvas);

#endif // CANVAS_H
