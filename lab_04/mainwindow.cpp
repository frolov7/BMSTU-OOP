#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setbuf(stdout, NULL);

	QObject::connect(this, SIGNAL(floor_selected(int)), &elevator, SLOT(call_button_pressed(int)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_QButtonFloor1_clicked()
{
	emit floor_selected(1);
}

void MainWindow::on_QButtonFloor2_clicked()
{
	emit floor_selected(2);
}

void MainWindow::on_QButtonFloor3_clicked()
{
	emit floor_selected(3);
}

void MainWindow::on_QButtonFloor4_clicked()
{
	emit floor_selected(4);
}

void MainWindow::on_QButtonFloor5_clicked()
{
	emit floor_selected(5);
}

void MainWindow::on_QButtonFloor6_clicked()
{
	emit floor_selected(6);
}

void MainWindow::on_QButtonFloor7_clicked()
{
	emit floor_selected(7);
}

void MainWindow::on_QButtonFloor8_clicked()
{
	emit floor_selected(8);
}

void MainWindow::on_QButtonFloor9_clicked()
{
	emit floor_selected(9);
}

void MainWindow::on_QButtonFloor10_clicked()
{
	emit floor_selected(10);
}