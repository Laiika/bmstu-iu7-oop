#ifndef LIFT_CONTROL_H
#define LIFT_CONTROL_H

#include <QWidget>
#include <QVBoxLayout>
#include <vector>
#include <QDebug>
#include <memory>
#include <QTimer>

#include "button.h"

#define FLOOR_COUNT 9
#define DOORS_TIME  500
#define MOVING_TIME 3000

enum Direction
{
    DOWN = -1,
    STOP = 0,
    UP = 1
};

class LiftControl : public QWidget
{
    Q_OBJECT;

    enum LiftControl_States
    {
        FREE,
        NEW_TARGET,
        BUSY
    };

public:
    explicit LiftControl(QWidget *parent = nullptr);
    ~LiftControl() = default;

public slots:
    void slot_new_target(int floor);
    void slot_passed_floor();
    void slot_move_cabin();

signals:
    void signal_stop_cabin();
    void signal_call_to_floor();

private:
    LiftControl_States state;
    Direction direction;
    int cur_floor;
    int need_floor;

    QTimer timer_cabin_move;

    std::vector<std::shared_ptr<Button>> buttons;
    std::vector<bool> visited_floors;
    std::unique_ptr<QVBoxLayout> layout;

    bool target_check(int &new_floor);

signals:
    void signal_floor_passed();
};


#endif // LIFT_CONTROL_H
