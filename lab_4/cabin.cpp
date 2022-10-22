#include <QDebug>
#include "cabin.h"

Cabin::Cabin(QObject *parent) : QObject(parent)
{
    state = STAND;

    QObject::connect(this, SIGNAL(signal_doors_open()), &door, SLOT(slot_opening()));
    QObject::connect(&door, SIGNAL(signal_door_closed()), this, SLOT(slot_cabin_wait()));
}

void Cabin::slot_cabin_moving()
{
    if (STAND == state || WAIT == state)
    {
        state = MOVING;
        emit signal_move_cabin();
    }
}

void Cabin::slot_cabin_wait()
{
    if (WAIT == state)
    {
        state = STAND;
        emit signal_find_new_target(-1);
    }
}

void Cabin::slot_cabin_stop()
{
    state = WAIT;
    emit signal_doors_open();
}

