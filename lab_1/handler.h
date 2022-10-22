#ifndef HANDLER_H
#define HANDLER_H

#include "figure.h"

enum commands {
    LOAD,
    DRAW,
    MOVE,
    SCALE,
    ROTATE,
    END
};


struct request
{
    commands command;
    point_t center;
    union
    {
        char const *filename;
        canvas_t canvas;
        coeffs_t coeffs;
    };
};
typedef struct request request_t;


rc_t request_handle(const request_t &req);

#endif // HANDLER_H
