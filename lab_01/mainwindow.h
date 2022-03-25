#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "requests.h"

#define window_x 750
#define window_y 570

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
private slots:
    void on_load_button_clicked();

    void on_move_button_clicked();

    void on_scale_button_clicked();

    void on_turn_button_clicked();

    err_t draw_actions(void);
};

#endif // MAINWINDOW_H
