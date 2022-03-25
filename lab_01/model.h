#ifndef MODEL_H
#define MODEL_H

#include "ui_mainwindow.h"
#include "draw_lines.h"
#include "points.h"
#include "lines.h"
#include "errors.h"

struct model
{
    pdata_t points;
    ldata_t lines;
};

using model_t = struct model;
using fname_t = const char *;

model &init(void);

err_t load_model(model_t &model, fname_t name);

err_t draw_model(const model_t &model, const canvas_t &canvas);

err_t move_model(model_t &model, const move_t &factor);

err_t scale_model(model_t &model, const scale_t &factor);

err_t turn_model(model_t &model, const turn &factor);

int free_model(const model_t &model);

#endif // MODEL_H
