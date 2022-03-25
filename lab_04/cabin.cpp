#include "cabin.h"
#include <iostream>
#include "ui_mainwindow.h"

Cabin::Cabin(QObject* parent) : QObject(parent)
{
    moving_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL(cabin_called()), this, SLOT(moving())); // соединяем сигнал cabin_called со слотом moving
    QObject::connect(this, SIGNAL(cabin_stopped()), &doors, SLOT(opening())); // соединяем сигнал cabin_stopped со слотом opening
    QObject::connect(this, SIGNAL(cabin_target_achieved()), this, SLOT(stop())); // соединяем сигнал cabin_target_achieved со слотом stop
    QObject::connect(&doors, SIGNAL(doors_closed()), this, SLOT(waiting())); // соединяем сигнал doors_closed со слотом waiting
    QObject::connect(&moving_timer, SIGNAL(timeout()), this, SLOT(moving())); // соединяем сигнал timeout со слотом moving
}

void Cabin::stop()
{
    if (state != MOVING) // если не в движении
        return;

    state = STOP; // состояние - остановка

    std::cout << "Stop on the " << current_floor << " floor" << std::endl;

    emit cabin_stopped();  // Doors::opening()
}

void Cabin::waiting()
{
    if (state != STOP) // если не стоим
        return;

    state = WAITING;

    std::cout << "Waiting..." << std::endl;

    emit cabin_wait(current_floor);  // Controller::free()
}

void Cabin::moving()
{
    if (state != GETTING && state != MOVING) // если еще не начали обработку и не поехали
        return;

    if (state == MOVING) // если уже едем
        current_floor += current_direction;

    state = MOVING;

    if (current_floor == current_target) // если доехали
        emit cabin_target_achieved();  // Cabin::stop()
    else
    {
        emit cabin_passed_floor(current_floor, current_direction);  // Controller::busy()
        moving_timer.start(MOVING_TIME);                            // Cabin::moving()
    }
}

void Cabin::get_target(int floor, const direction_t& direction)
{
    if (state != WAITING)
        return;

    state = GETTING; // готовка

    current_target = floor;
    current_direction = direction;

    emit cabin_called();  // Cabin::moving()
}
