#ifndef POINTS_H
#define POINTS_H

#include "return_codes.h"
#include <stdio.h>
#include <stdlib.h>

struct point
{
    double x;
    double y;
    double z;
};
typedef struct point point_t;

struct points
{
    int size;
    point_t *arr;
};
typedef struct points points_t;

struct coeffs
{
    double x;
    double y;
    double z;
};
typedef struct coeffs coeffs_t;


rc_t points_read(points_t &points, FILE *f);
void points_free(const points_t &points);
void points_rotate(points_t &points, const coeffs_t &cfs, const point_t &center);
void points_scale(points_t &points, const coeffs_t &cfs, const point_t &center);
void points_move(points_t &points, const coeffs_t &cfs);

#endif // POINTS_H
