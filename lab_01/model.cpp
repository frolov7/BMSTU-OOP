#include "model.h"

// Инициализация модели
model &init(void)
{
    static model_t model;

    model.lines.arr = NULL;
    model.lines.size = 0;

    model.points.arr = NULL;
    model.points.size = 0;

    return model;
}

static err_t load_temp_model(model_t &temp_model, FILE *f)
{
    err_t rc = SUCCESS;
    if ((rc = handle_points(temp_model.points, f)))
        return rc;

    if ((rc = handle_lines(temp_model.lines, f)))
        free_points(temp_model.points);

    return rc;
}

// Загрузка модели
err_t load_model(model_t &model, fname_t name)
{
    FILE *f = NULL;

    if ((f = fopen(name, "r")) == NULL)
        return FILE_ERROR;

    err_t rc = SUCCESS;

    model_t temp_model = init();
    rc = load_temp_model(temp_model, f); // !!!!
    fclose(f);

    if (!rc)
    {
        free_model(model);
        model = temp_model;
    }

    return rc;
}

static int scale_points(pdata_t &points, const scale_t &factor)
{
    for (int i = 0; i < points.size; i++)
        scale_point(points.arr[i], factor);

    return SUCCESS;
}

// Масштаб модели
err_t scale_model(model_t &model, const scale_t &factor)
{
    if (model.points.arr == NULL || model.lines.arr == NULL)
        return MEMORY_ERROR;

    scale_points(model.points, factor);

    return SUCCESS;
}

static int turn_points(pdata_t &points, const turn &factor)
{
    for (int i = 0; i < points.size; i++)
    {
        turn_x_point(points.arr[i], factor.ox);
        turn_y_point(points.arr[i], factor.oy);
        turn_z_point(points.arr[i], factor.oz);
    }

    return SUCCESS;
}

// Вращение модели
err_t turn_model(model_t &model, const turn &factor)
{
    if (model.points.arr == NULL || model.lines.arr == NULL)
        return MEMORY_ERROR;

    turn_points(model.points, factor);

    return SUCCESS;
}

static int move_points(pdata_t &points, const move_t &factor)
{
    for (int i = 0; i < points.size; i++)
        move_point(points.arr[i], factor);

    return SUCCESS;
}

// Перемещение модели
err_t move_model(model_t &model, const move_t &factor)
{
    if (model.points.arr == NULL || model.lines.arr == NULL)
        return MEMORY_ERROR;

    move_points(model.points, factor);

    return SUCCESS;
}

// Вывод модели
err_t draw_model(const model_t &model, const canvas_t &canvas)
{
    if (model.lines.arr == NULL || model.points.arr == NULL)
        return MEMORY_ERROR;

    canvas.scene->clear();
    draw_lines(model.lines, model.points, canvas);

    return SUCCESS;
}

// Очистка памяти от модели
int free_model(const model_t &model)
{
    free_points(model.points);
    free_lines(model.lines);

    return SUCCESS;
}
