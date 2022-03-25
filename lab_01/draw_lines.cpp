#include "draw_lines.h"

// Вывод на канвас
static int draw_line(const line_t &line, const point_t *points, const canvas_t &canvas)
{
    point_t pt1 = points[line.point_first];
    point_t pt2 = points[line.point_second];

    canvas.scene->addLine(pt1.x + canvas.width / 2, pt1.y + canvas.height / 2, pt2.x + canvas.width / 2, pt2.y + canvas.height / 2);

    return SUCCESS;
}

// Вывод линий
int draw_lines(const ldata_t &lines, const pdata_t &points, const canvas_t &canvas)
{
    for (int i = 0; i < lines.size; i++)
        draw_line(lines.arr[i], points.arr, canvas);

    return SUCCESS;
}
