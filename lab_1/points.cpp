#include "points.h"
#include <stdlib.h>
#include <cmath>

static rc_t points_arr_allocate(points_t &points)
{
    points.arr = (point_t *)malloc(points.size * sizeof(point_t));

    if (NULL == points.arr)
        return MEMORY_ERROR;

    return OK;
}

void points_free(const points_t &points)
{
    free(points.arr);
}

static rc_t points_cnt_read(points_t &points, FILE *f)
{
    if (1 != fscanf(f, "%d", &points.size))
        return INPUT_ERROR;

    if (points.size < 2)
        return SIZE_ERROR;

    return OK;
}

static rc_t point_read(point_t &point, FILE *f)
{
    if (3 != fscanf(f, "%lf %lf %lf", &point.x, &point.y, &point.z))
        return INPUT_ERROR;

    return OK;
}

static rc_t points_arr_read(points_t &points, FILE *f)
{
    rc_t rc = OK;

    for (int i = 0; OK == rc && i < points.size; i++)
       rc = point_read(points.arr[i], f);

    return rc;
}

rc_t points_read(points_t &points, FILE *f)
{
    rc_t rc = points_cnt_read(points, f);
    if (OK == rc)
    {
        rc = points_arr_allocate(points);
        if (OK == rc)
        {
            rc = points_arr_read(points, f);
            if (rc != OK)
                points_free(points);
        }
    }

    return rc;
}


static double to_rads(const double ang)
{
    return ang * M_PI / 180.0;
}

static void xpoint_rotate(point_t &point, const double ang)
{
    double y_tmp = point.y;
    double ang_cos = cos(to_rads(ang));
    double ang_sin = sin(to_rads(ang));

    point.y = point.y * ang_cos + point.z * ang_sin;
    point.z = point.z * ang_cos - y_tmp * ang_sin;
}

static void ypoint_rotate(point_t &point, const double ang)
{
    double x_tmp = point.x;
    double ang_cos = cos(to_rads(ang));
    double ang_sin = sin(to_rads(ang));

    point.x = point.x * ang_cos + point.z * ang_sin;
    point.z = point.z * ang_cos - x_tmp * ang_sin;
}

static void zpoint_rotate(point_t &point, const double ang)
{
    double x_tmp = point.x;
    double ang_cos = cos(to_rads(ang));
    double ang_sin = sin(to_rads(ang));

    point.x = point.x * ang_cos + point.y * ang_sin;
    point.y = point.y * ang_cos - x_tmp * ang_sin;
}

static void point_move_to_center(point_t &point, const point_t &center)
{
    point.x -= center.x;
    point.y -= center.y;
    point.z -= center.z;
}

static void point_move_back(point_t &point, const point_t &center)
{
    point.x += center.x;
    point.y += center.y;
    point.z += center.z;
}

static void point_rotate(point_t &point, const coeffs_t &cfs, const point_t &center)
{
    point_move_to_center(point, center);

    xpoint_rotate(point, cfs.x);
    ypoint_rotate(point, cfs.y);
    zpoint_rotate(point, cfs.z);

    point_move_back(point, center);
}

void points_rotate(points_t &points, const coeffs_t &cfs, const point_t &center)
{
    for (int i = 0; i < points.size; i++)
        point_rotate(points.arr[i], cfs, center);
}

static void point_scale(point_t &point, const coeffs_t &cfs, const point_t &center)
{
    point.x = point.x * cfs.x + (1 - cfs.x) * center.x;
    point.y = point.y * cfs.y + (1 - cfs.y) * center.y;
    point.z = point.z * cfs.z + (1 - cfs.z) * center.z;
}

void points_scale(points_t &points, const coeffs_t &cfs, const point_t &center)
{
    for (int i = 0; i < points.size; i++)
        point_scale(points.arr[i], cfs, center);
}

static void point_move(point_t &point, const coeffs_t &cfs)
{
    point.x += cfs.x;
    point.y += cfs.y;
    point.z += cfs.z;
}

void points_move(points_t &points, const coeffs_t &cfs)
{
    for (int i = 0; i < points.size; i++)
        point_move(points.arr[i], cfs);
}
