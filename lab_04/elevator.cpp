#include "elevator.h"

Elevator::Elevator(QObject *parent): QObject(parent)
{
    QObject::connect(&cabin, SIGNAL(cabin_wait(int)), &control_device, SLOT(free(int))); // соединяем сигнал cabin_wait со слотом free
    QObject::connect(&cabin, SIGNAL(cabin_passed_floor(int, direction_t)), &control_device, SLOT(busy(int, direction_t))); // соединяем сигнал cabin_passed_floor со слотом busy
    QObject::connect(&control_device, SIGNAL(new_target_signal(int, direction_t)), &cabin, SLOT(get_target(int, direction_t))); // соединяем сигнал new_target_signal со слотом get_target
}

void Elevator::call_button_pressed(int floor)
{
	control_device.new_target(floor);
}
