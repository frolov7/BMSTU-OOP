#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <vector>
#include "direction.h"

#define FLOOR_NUMBER 10

class Controller : public QObject
{
    Q_OBJECT

    enum state_t
    {
        FREE,
        BUSY
    };

public:
    explicit Controller(QObject* parent = nullptr);
    void new_target(int floor);

public slots:
    void free(int floor);
    void busy(int floor, const direction_t& direction);

signals:
    void new_target_signal(int floor, const direction_t& direction);

private:
    direction_t current_direction = STAY; // текущее направление - стоять
    int current_floor = 1; // текущий этаж - 1
    int current_target = 0; // текущая цель - 0
    state_t state = FREE; // состояние - свободно

    void next_target();

    std::vector<bool> targets;
};

#endif  // CONTROLLER_H
