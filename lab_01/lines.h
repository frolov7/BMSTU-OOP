#ifndef lineS_H
#define lineS_H

#include <stdio.h>
#include <stdlib.h>

#include "ui_mainwindow.h"
#include "errors.h"
#include "points.h"

struct line
{
    int point_first;
    int point_second;
};

using line_t = struct line;

struct lines_data
{
    int size = 0;
    line_t *arr = NULL;
};

using ldata_t = struct lines_data;

err_t handle_lines(ldata_t &lines, FILE *file);

int free_lines(const ldata_t &lines);

#endif // lineS_H
