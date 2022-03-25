#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "elevator.h"
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

signals:
	void floor_selected(int floor);

private slots:
	void on_QButtonFloor1_clicked();

	void on_QButtonFloor2_clicked();

	void on_QButtonFloor3_clicked();

	void on_QButtonFloor4_clicked();

	void on_QButtonFloor5_clicked();

	void on_QButtonFloor6_clicked();

	void on_QButtonFloor7_clicked();

	void on_QButtonFloor8_clicked();

	void on_QButtonFloor9_clicked();

	void on_QButtonFloor10_clicked();

private:
	Ui::MainWindow *ui;

	Elevator elevator;
};
#endif // MAINWINDOW_H
