#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include "cabin.h"
#include "controller.h"

class Elevator : public QObject
{
    Q_OBJECT

public:
    explicit Elevator(QObject* parent = nullptr);

public slots:
    void call_button_pressed(int floor);

private:
    Cabin cabin; // объект кабины
    Controller control_device; // объект контроллера
};

#endif  // LIFT_H
