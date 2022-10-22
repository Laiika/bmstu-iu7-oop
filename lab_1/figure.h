#ifndef FIGURE_H
#define FIGURE_H

#include "points.h"
#include "pairs.h"
#include "return_codes.h"
#include "canvas.h"

struct figure
{
    points_t points;
    pairs_t pairs;
};
typedef struct figure figure_t;


figure_t &figure_init();
void figure_free(const figure_t &figure);
rc_t figure_load(figure_t &figure, char const *filename);
rc_t figure_draw(const figure_t &figure, const canvas_t &canvas);
rc_t figure_rotate(figure_t &figure, const coeffs_t &cfs, const point_t &center);
rc_t figure_scale(figure_t &figure, const coeffs_t &cfs, const point_t &center);
rc_t figure_move(figure_t &figure, const coeffs_t &cfs);

#endif // FIGURE_H
