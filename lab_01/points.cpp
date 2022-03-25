#include "points.h"

double to_radians(double (*f)(double), const double &alpha)
{
    return (*f)(alpha * PI / 180);
}

// Считывание количества точек
static err_t read_amount(pdata_t &points, FILE *file)
{
    if ((fscanf(file, "%d", &points.size)) != 1)
        return READ_ERROR;

    if (points.size < 2)
        return PSIZE_ERROR;

    return SUCCESS;
}

// ввод точек
static err_t read_points(pdata_t &points, FILE *file)
{
    err_t rc = SUCCESS;

    for (int i = 0; i < points.size; i++)
    {
        if ((fscanf(file, "%lf %lf %lf", &points.arr[i].x, &points.arr[i].y, &points.arr[i].z)) != 3)
        {
            rc = READ_ERROR;  // !!!!
            break;
        }
    }
    return rc;
}

// Выделение памяти для точек
static err_t allocate_lines(pdata_t &points)
{
    point_t *tmp_arr = (point_t *)malloc(points.size * sizeof(point_t));

    if (tmp_arr == NULL)
        return ALLOCATION_ERROR;

    points.arr = tmp_arr;

    return SUCCESS;
}

// Очистка памяти от точек
int free_points(const pdata_t &points)
{
    if (points.arr != NULL)
        free(points.arr);

    return SUCCESS;
}

// Считывание точек
err_t handle_points(pdata_t &points, FILE *file)
{
    err_t rc = SUCCESS;

    if ((rc = read_amount(points, file))) // Чтение количества точек
        return rc;

    if ((rc = allocate_lines(points))) // Выделение памяти
        return rc;

    if ((rc = read_points(points, file))) // Ввод точек  // !!!!
        free_points(points);

    return rc;
}

// Перемещение по точкам
int move_point(point_t &point, const move_t &factor)
{
    point.x += factor.dx;
    point.y += factor.dy;
    point.z += factor.dz;

    return SUCCESS;
}

// масштаб по точкам
int scale_point(point_t &point, const scale_t &factor)
{
    point.x *= factor.kx;
    point.y *= factor.ky;
    point.z *= factor.kz;

    return SUCCESS;
}

// Вращение х
int turn_x_point(point_t &point, const double &alpha)
{
    double cos_radians = to_radians(cos, alpha);
    double sin_radians = to_radians(sin, alpha);
    double tmp_y = point.y;

    point.y = point.y * cos_radians + point.z * sin_radians;
    point.z = -tmp_y * sin_radians + point.z * cos_radians;

    return SUCCESS;
}

// Вращение у
int turn_y_point(point_t &point, const double &alpha)
{
    double cos_radians = to_radians(cos, alpha);
    double sin_radians = to_radians(sin, alpha);
    double tmp_x = point.x;

    point.x = point.x * cos_radians + point.z * sin_radians;
    point.z = -tmp_x * sin_radians + point.z * cos_radians;

    return SUCCESS;
}

// Вращение z
int turn_z_point(point_t &point, const double &alpha)
{
    double cos_radians = to_radians(cos, alpha);
    double sin_radians = to_radians(sin, alpha);
    double tmp_x = point.x;

    point.x = point.x * cos_radians + point.y * sin_radians;
    point.y = -tmp_x * sin_radians + point.y * cos_radians;

    return SUCCESS;
}

