#ifndef REQUEST_H
#define REQUEST_H

#include "model.h"

enum data
{
    LOAD_MODEL,
    SCALE_MODEL,
    TURN_MODEL,
    MOVE_MODEL,
    DRAW_MODEL,
    QUIT
};

struct request
{
    int task;
    union
    {
        canvas_t canvas;
        fname_t file_name;
        scale_t scale;
        turn_t turn;
        move_t move;
    };
};

using request_t = struct request;

err_t requests(const request_t &request);

#endif // REQUESTS_H
