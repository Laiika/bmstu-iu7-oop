#include "lift.h"
#include <QPalette>

Lift::Lift(QObject *parent) : QObject(parent)
{
    this->control.setStyleSheet("background-color:green;");

    QObject::connect(&control, SIGNAL(signal_call_to_floor()), &cabin, SLOT(slot_cabin_moving()));
    QObject::connect(&cabin, SIGNAL(signal_move_cabin()), &control, SLOT(slot_move_cabin()));
    QObject::connect(&control, SIGNAL(signal_stop_cabin()), &cabin, SLOT(slot_cabin_stop()));
    QObject::connect(&cabin, SIGNAL(signal_find_new_target(int)), &control, SLOT(slot_new_target(int)));
}

QWidget *Lift::widget()
{
    return &this->control;
}
