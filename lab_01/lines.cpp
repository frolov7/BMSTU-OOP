#include "lines.h"

// Считывание количества линий
static err_t read_amount(ldata_t &lines, FILE *file)
{
    if ((fscanf(file, "%d", &lines.size)) != 1)
        return READ_ERROR;

    if (lines.size < 1)
        return LSIZE_ERROR;

    return SUCCESS;
}

// Выделение памяти под линии
static err_t allocate_lines(ldata_t &lines)
{
    line_t *tmp_arr = (line_t *)malloc(lines.size * sizeof(line_t));

    if (tmp_arr == NULL)
        return ALLOCATION_ERROR;

    lines.arr = tmp_arr;

    return SUCCESS;
}

// Считывание линий
static err_t read_lines(ldata_t &lines, FILE *file)
{
    err_t rc = SUCCESS;
    for (int i = 0; i < lines.size; i++)
    {
        if ((fscanf(file, "%d %d", &lines.arr[i].point_first, &lines.arr[i].point_second)) != 2) // Связка двух точек
        {
            rc = READ_ERROR;  // !!!!
            break;
        }
    }

    return rc;
}

// Очистка памяти
int free_lines(const ldata_t &lines)
{
    if (lines.arr != NULL)
        free(lines.arr);

    return SUCCESS;
}

// Ввод линий
err_t handle_lines(ldata_t &lines, FILE *file)
{
     err_t rc = SUCCESS;

     if ((rc = read_amount(lines, file))) // Количество линий  // !!!!
         return rc;

     if ((rc = allocate_lines(lines))) // Выделение памяти под линии
         return rc;

     if ((rc = read_lines(lines, file))) // Считывание линий  // !!!!
         free_lines(lines);

     return rc;
}
