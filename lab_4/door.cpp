#include "door.h"
#include "lift_control.h"

Door::Door()
{
    state = CLOSED;

    QObject::connect(&timer_opening,  SIGNAL(timeout()), this, SLOT(slot_open()));
    QObject::connect(&timer_opened,  SIGNAL(timeout()), this, SLOT(slot_closing()));
    QObject::connect(&timer_closing, SIGNAL(timeout()), this, SLOT(slot_close()));
}


void Door::slot_opening()
{
    if (CLOSED == state || CLOSING == state)
    {
        qDebug() << "Двери открываются";

        if (CLOSED == state)
            timer_opening.start(DOORS_TIME);
        else
        {
            auto timer = timer_closing.remainingTime();
            timer_closing.stop();
            timer_opening.start(DOORS_TIME - timer);
        }

        state = OPENING;
    }
}


void Door::slot_open()
{
    if (OPENING == state)
    {
        state = OPEN;
        qDebug() << "Двери открыты";

        timer_opened.start(DOORS_TIME);
    }
}


void Door::slot_closing()
{
    if (OPEN == state)
    {
        state = CLOSING;
        qDebug() << "Двери закрываются";
        timer_closing.start(DOORS_TIME);
    }
}


void Door::slot_close()
{
    if (CLOSING == state)
    {
        state = CLOSED;
        qDebug() << "Двери закрыты\n";

        emit signal_door_closed();
    }
}
