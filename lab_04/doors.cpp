#include "doors.h"
#include <iostream>

Doors::Doors(QObject *parent): QObject(parent)
{
    stay_timer.setInterval(STAY_TIME); // интервал таймера в мс

	stay_timer.setSingleShot(true);
	closing_timer.setSingleShot(true);
	opening_timer.setSingleShot(true);

    QObject::connect(&closing_timer, SIGNAL(timeout()), this, SLOT(closed())); // соед-м сигнал timeout со слотом closed
    QObject::connect(&opening_timer, SIGNAL(timeout()), this, SLOT(opened())); // соед-м сигнал timeout со слотом opened
    QObject::connect(this, SIGNAL(doors_opened()), &stay_timer, SLOT(start())); // соед-м сигнал doors_opened со слотом start
    QObject::connect(&stay_timer, SIGNAL(timeout()), this, SLOT(closing())); // соед-м сигнал timeout со слотом closing
}

void Doors::closing()
{
    if (state != OPENED) // если открылись
		return;

    std::cout << "Doors are closing..." << std::endl;

    state = CLOSING; // состояние закрытия
	closing_timer.start(CLOSING_TIME); // Doors::closed()
}

void Doors::opening()
{
    if (state != CLOSED && state != CLOSING) // если не закрыты и не закрываются
		return;

    std::cout << "Doors are opening..." << std::endl;

    if (state == CLOSED) // если закрыты
	{
        state = OPENING; // то открываются
		opening_timer.start(OPENING_TIME); // Doors::closed
	}
	else if (state == CLOSING)
	{
        state = OPENING; // открываются
        int left_time = closing_timer.remainingTime();
		closing_timer.stop();
        opening_timer.start(OPENING_TIME - left_time); // Doors::closed
	}
}

void Doors::closed()
{
    if (state != CLOSING) // если закрываются
		return;

    std::cout << "Doors closed" << std::endl;

    state = CLOSED; // закрыли

	emit doors_closed(); // Cabin::wait
}

void Doors::opened()
{
    if (state != OPENING) // если открываются
		return;

    std::cout << "Doors opened" << std::endl;

    state = OPENED; // открыли

	emit doors_opened(); // Cabin::wait
}
