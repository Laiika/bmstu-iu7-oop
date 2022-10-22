#include "figure.h"

figure_t &figure_init()
{
    static figure_t figure;

    figure.points.arr = NULL;
    figure.points.size = 0;
    figure.pairs.arr = NULL;
    figure.pairs.size = 0;

    return figure;
}

void figure_free(const figure_t &figure)
{
    points_free(figure.points);
    pairs_free(figure.pairs);
}

static rc_t figure_tmp_load(figure_t &tmp, FILE *f)
{
    rc_t rc = points_read(tmp.points, f);

    if (OK == rc)
    {
        rc = pairs_read(tmp.pairs, f);

        if (OK != rc)
            points_free(tmp.points);
    }

    return rc;
}

rc_t figure_load(figure_t &figure, char const * filename)
{
    FILE *f = NULL;

    if (NULL == (f = fopen(filename, "r")))
        return FILE_ERROR;

    figure_t tmp = figure_init();

    rc_t rc = figure_t
            mp_load(tmp, f);
    fclose(f);
    if (OK == rc)
    {
        figure_free(figure);
        figure = tmp;
    }

    return rc;
}

rc_t figure_draw(const figure_t &figure, const canvas_t &canvas)
{
    if (NULL == figure.points.arr)
        return NO_FIGURE;

    canvas_clear(canvas);
    draw_lines(figure.points, figure.pairs, canvas);
    return OK;
}

rc_t figure_rotate(figure_t &figure, const coeffs_t &cfs, const point_t &center)
{
    if (NULL == figure.points.arr)
        return NO_FIGURE;

    points_rotate(figure.points, cfs, center);
    return OK;
}

rc_t figure_scale(figure_t &figure, const coeffs_t &cfs, const point_t &center)
{
    if (NULL == figure.points.arr)
        return NO_FIGURE;

    points_scale(figure.points, cfs, center);
    return OK;
}

rc_t figure_move(figure_t &figure, const coeffs_t &cfs)
{
    if (NULL == figure.points.arr)
        return NO_FIGURE;

    points_move(figure.points, cfs);
    return OK;
}
