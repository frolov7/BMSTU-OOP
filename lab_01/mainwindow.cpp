#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, window_x, window_y);
}

MainWindow::~MainWindow(void)
{
    request_t request;
    requests(request);

    delete ui;
}

err_t MainWindow::draw_actions(void)
{
    canvas_t canvas;
    canvas.scene = ui->graphicsView->scene();
    canvas.width = canvas.scene->width();
    canvas.height = canvas.scene->height();

    request_t request;
    request.task = DRAW_MODEL;
    request.canvas = canvas;

    err_t rc = requests(request);

    return rc;
}

// Кнопка для загрузки модели
void MainWindow::on_load_button_clicked(void)
{
    fname_t name = "C:/Users/gimna/Desktop/BMSTU/OOP/labs/lab_01/data.csv";
    request_t request;
    request.task = LOAD_MODEL;
    request.file_name = name;

    err_t rc = requests(request);
    if (rc)
    {
        errors(rc);
        return;
    }

    rc = draw_actions();
    if (rc)
        errors(rc);
}

// кнопки для перемещения
void MainWindow::on_move_button_clicked(void)
{
    move_t factor;
    factor.dx = ui->dx_box->value();
    factor.dy = ui->dy_box->value();
    factor.dz = ui->dz_box->value();

    request_t request;
    request.task = MOVE_MODEL;
    request.move = factor;

    err_t rc = requests(request);
    if (rc)
    {
        errors(rc);
        return;
    }

    rc = draw_actions();
    if (rc)
        errors(rc);
}

// кнопки для масштабирования
void MainWindow::on_scale_button_clicked(void)
{
    scale_t factor;
    factor.kx = ui->kx_box->value();
    factor.ky = ui->ky_box->value();
    factor.kz = ui->kz_box->value();

    request_t request;
    request.task = SCALE_MODEL;
    request.scale = factor;

    err_t rc = requests(request);
    if (rc)
    {
        errors(rc);
        return;
    }

    rc = draw_actions();
    if (rc)
        errors(rc);
}

// кнопки для вращения
void MainWindow::on_turn_button_clicked(void)
{
    turn_t factor;
    factor.ox = ui->ox_box->value();
    factor.oy = ui->oy_box->value();
    factor.oz = ui->oz_box->value();

    request_t request;
    request.task = TURN_MODEL;
    request.turn = factor;

    err_t rc = requests(request);
    if (rc)
    {
        errors(rc);
        return;
    }

    rc = draw_actions();

    if (rc)
        errors(rc);
}
