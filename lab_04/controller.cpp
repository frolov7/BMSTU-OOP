#include "controller.h"
#include <iostream>

Controller::Controller(QObject *parent): QObject(parent)
{
    targets.resize(FLOOR_NUMBER); // кол-во этажей

    for (auto floor: targets)
        floor = false;

    QObject::connect(this, SIGNAL(new_target_signal(int, direction_t)), this, SLOT(busy(int, direction_t))); // соед-м сигнал new_target_signal со слотом busy
}

void Controller::busy(int floor, const direction_t &direction)
{
    if (state == FREE) // если стоим
	{
        state = BUSY; // то начинаем ехать
		current_target = floor;
		current_direction = direction;
	}
	else
	{
        std::cout << "Current floor: " << floor << std::endl;
		current_floor += current_direction;
	}
}

void Controller::free(int floor)
{
	state = FREE;
	current_floor = floor;
	next_target();
}

void Controller::next_target()
{
    if (targets[current_floor - 1]) // доехали до цели
    {
        targets[current_floor - 1] = false; // помечаем его как пройденный
		emit new_target_signal(current_floor, STAY); // Controller::busy(current_floor, STAY); Cabin::get_target()
	}
	else
	{
        int running_floor = 0;
        while (running_floor < (int) (targets.size()) && !targets[running_floor]) // пока не доехали до последнего и цель != тру
            running_floor++;

        if (running_floor >= 0 && running_floor < (int) (targets.size())) // в пределах этажей
		{
            targets[running_floor] = false; // значит доехали и он фолс

            emit running_floor > current_floor - 1 ? new_target_signal(running_floor + 1, UP) : new_target_signal(running_floor + 1, DOWN); // Controller::busy(); Cabin::get_target()
		}
	}
}

void Controller::new_target(int floor)
{
    std::cout << "New target is located on the floor " << floor << std::endl;
    targets[floor - 1] = true; // помечаем нужный этаж цель

	if (state == FREE)
		next_target();
}
