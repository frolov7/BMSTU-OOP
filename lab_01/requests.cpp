#include "requests.h"

err_t requests(const request_t &request)
{
    static model_t model = init();
    err_t rc = SUCCESS;

    switch (request.task)
    {
        case LOAD_MODEL:
            rc = load_model(model, request.file_name);
            break;
        case SCALE_MODEL:
            rc = scale_model(model, request.scale);
            break;
        case TURN_MODEL:
            rc = turn_model(model, request.turn);
            break;
        case MOVE_MODEL:
            rc = move_model(model, request.move);
            break;
        case DRAW_MODEL:
            rc = draw_model(model, request.canvas);
            break;
        case QUIT:
            free_model(model);
            break;
        default:
            rc = UNKNOWN_COMMAND;
    }

    return rc;
}
