#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include <QTimer>
#include "doors.h"
#include "direction.h"

#define MOVING_TIME 1500

class Cabin : public QObject
{
    Q_OBJECT

    enum state_t
    {
        STOP,
        WAITING,
        GETTING,
        MOVING
    };

public:
    explicit Cabin(QObject* parent = nullptr);

    signals:
        void cabin_called(); // вызов кабины
        void cabin_stopped(); // остановка кабины
        void cabin_target_achieved(); // дошли до конца
        void cabin_passed_floor(int floor, const direction_t& direction); // прошли этаж
        void cabin_wait(int floor); // ожидание

public slots:
    void stop();
    void waiting();
    void get_target(int floor, const direction_t& direction);
    void moving();

private:
    Doors doors; // объект doors
    direction_t current_direction = STAY; // текущее состояние = стоим
    state_t state = WAITING; // состояние ждем
    int current_floor = 1; // текущий этаж - 1
    int current_target = 0; // цель - 0

    QTimer moving_timer;
};

#endif  // CAGE_H
