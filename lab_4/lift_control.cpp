#include "lift_control.h"

LiftControl::LiftControl(QWidget *parent) : QWidget(parent)
{
    this->layout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
    this->setLayout(this->layout.get());

    QObject::connect(&timer_cabin_move, SIGNAL(timeout()), this, SLOT(slot_move_cabin()));
    QObject::connect(this, SIGNAL(signal_floor_passed()), this, SLOT(slot_passed_floor()));

    state = FREE;
    cur_floor = 1;
    need_floor = 1;
    direction = STOP;

    for (int i = 0; i < FLOOR_COUNT; i++)
    {
        std::shared_ptr<Button> btn(new Button);
        btn->set_floor(FLOOR_COUNT - i);
        btn->setText(QString::number(FLOOR_COUNT - i));

        buttons.insert(buttons.begin(), btn);
        layout->addWidget(btn.get());

        visited_floors.push_back(true);
        QObject::connect(btn.get(), SIGNAL(signal_press(int)), this, SLOT(slot_new_target(int)));
    }
}

void LiftControl::slot_new_target(int floor)
{
    if (floor >= 1)
        this->visited_floors[floor - 1] = false;

    if (target_check(floor))
    {
        this->visited_floors[floor - 1] = false;
        this->state = NEW_TARGET;
        this->need_floor = floor;

        direction = need_floor > cur_floor ? UP : DOWN;
        emit signal_call_to_floor();
    }
}

void LiftControl::slot_move_cabin()
{
    state = BUSY;

    if (need_floor == cur_floor)
    {
        timer_cabin_move.stop();
        emit signal_floor_passed();
    }
    else
    {
        qDebug() << "Лифт на этаже " << cur_floor;

        cur_floor += direction;
        timer_cabin_move.start(MOVING_TIME);
    }
}

void LiftControl::slot_passed_floor()
{
    if (state == BUSY)
    {
        buttons[cur_floor - 1]->slot_unpress();
        this->visited_floors[need_floor - 1] = true;
        qDebug() << "Лифт остановился на этаже " << cur_floor;

        emit signal_stop_cabin();
    }
}


bool LiftControl::target_check(int &new_floor)
{
    int direction = this->direction != STOP ? this->direction : DOWN;

    for (int i = cur_floor - 1; i >= 0 && i < FLOOR_COUNT; i += direction)
    {
        if (!visited_floors[i])
        {
            new_floor = i + 1;
            return true;
        }
    }

    for (int i = cur_floor - 1; i >= 0 && i < FLOOR_COUNT; i += -direction)
    {
        if (!visited_floors[i])
        {
            new_floor = i + 1;
            return true;
        }
    }

    return false;
}
