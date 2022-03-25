#ifndef POINTS_H
#define POINTS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "errors.h"

#define PI 3.14

struct point
{
    double x;
    double y;
    double z;
};

using point_t = struct point;

struct points_data
{
    int size = 0;
    point_t *arr = NULL;
};

using pdata_t = struct points_data;

struct move
{
    double dx;
    double dy;
    double dz;
};

struct scale
{
    double kx;
    double ky;
    double kz;
};

struct turn
{
    double ox;
    double oy;
    double oz;
};

using move_t = struct move;
using scale_t = struct scale;
using turn_t = struct turn;

err_t handle_points(pdata_t &points, FILE *file);

int move_point(point_t &point, const move_t &factor);

int scale_point(point_t &point, const scale_t &factor);

int turn_x_point(point_t &point, const double &angle);

int turn_y_point(point_t &point, const double &angle);

int turn_z_point(point_t &point, const double &angle);

int free_points(const pdata_t &points);

#endif // POINTS_H
