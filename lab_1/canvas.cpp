#include "canvas.h"

void canvas_clear(const canvas_t &canvas)
{
    canvas.scene->clear();
}

static void draw_line(const points_t &points, const pair_t &pair, const canvas_t &canvas)
{
    int p1_ind = pair.point1;
    int p2_ind = pair.point2;
    point_t point1 = points.arr[p1_ind];
    point_t point2 = points.arr[p2_ind];

    canvas.scene->addLine(
        point1.x,
        point1.y,
        point2.x,
        point2.y,
        QPen(Qt :: green, 3)
   );
}

void draw_lines(const points_t &points, const pairs_t &pairs, const canvas_t &canvas)
{
    for (int i = 0; i < pairs.size; i++)
        draw_line(points, pairs.arr[i], canvas);
}
