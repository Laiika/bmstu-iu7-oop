#ifndef LIFT_H
#define LIFT_H

#include <QObject>

#include "lift_control.h"
#include "cabin.h"

class Lift : public QObject
{
    Q_OBJECT;

public:
    explicit Lift(QObject *parent = nullptr);
    ~Lift() = default;

    QWidget *widget();

private:
    LiftControl control;
    Cabin cabin;
};

#endif // LIFT_H
