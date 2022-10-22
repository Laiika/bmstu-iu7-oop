#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include "door.h"
#include "lift_control.h"


class Cabin : public QObject
{
    Q_OBJECT

    enum CabinStates
    {
        STAND,
        WAIT,
        MOVING
    };

public:
    explicit Cabin(QObject *parent = nullptr);
    ~Cabin() = default;

signals:
    void signal_doors_open();
    void signal_move_cabin();
    void signal_find_new_target(int);

public slots:
    void slot_cabin_stop();
    void slot_cabin_wait();
    void slot_cabin_moving();

private:
    Door door;
    CabinStates state;

};


#endif // CABIN_H
