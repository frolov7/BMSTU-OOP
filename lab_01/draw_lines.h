#ifndef DRAW_LINES_H
#define DRAW_LINES_H

#include "ui_mainwindow.h"
#include "points.h"
#include "lines.h"

struct canvas
{
    QGraphicsScene *scene;
    double width;
    double height;
};

using canvas_t = struct canvas;

int draw_lines(const ldata_t &lines, const pdata_t &points, const canvas_t &canvas);

#endif // DRAW_LINES_H
