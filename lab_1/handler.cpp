#include "handler.h"

rc_t request_handle(const request_t &req)
{
    rc_t rc = OK;
    static figure_t figure = figure_init();

    switch (req.command)
    {
        case DRAW:
            rc = figure_draw(figure, req.canvas);
            break;
        case LOAD:
            rc = figure_load(figure, req.filename);
            break;
        case SCALE:
            rc = figure_scale(figure, req.coeffs, req.center);
            break;
        case ROTATE:
            rc = figure_rotate(figure, req.coeffs, req.center);
            break;
        case MOVE:
            rc = figure_move(figure, req.coeffs);
            break;
        case END:
            figure_free(figure);
            break;
        default:
            rc = UNKNOWN_COMMAND;
    }

    return rc;
}
