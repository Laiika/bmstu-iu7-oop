#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

class Door : public QObject
{
    Q_OBJECT

    enum DoorStates
    {
        OPEN,
        OPENING,
        CLOSING,
        CLOSED
    };

public:
    Door();
    ~Door() = default;

signals:
    void signal_door_closed();

public slots:
    void slot_open();

private slots:
    void slot_opening();
    void slot_closing();
    void slot_close();

private:
    DoorStates state;

    QTimer timer_opening;
    QTimer timer_closing;
    QTimer timer_opened;
};

#endif // DOOR_H
