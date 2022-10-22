#include "button.h"
#include <QDebug>


Button::Button(QWidget *parent) : QPushButton(parent)
{
    // соединяем сигнал со слотом
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(slot_press()));
    QObject::connect(this, SIGNAL(signal_unpress()), this, SLOT(slot_unpress()));

    this->state = INACTIVE;
    this->floor = 1;
}


void Button::set_floor(const int &floor)
{
    this->floor = floor;
}

void Button::slot_press()
{
    if (INACTIVE == state)
    {
        this->setStyleSheet("background-color:pink;");
        this->update();

        this->state = ACTIVE;
        this->setDisabled(true);

        emit signal_press(floor);
    }
}

void Button::slot_unpress()
{
    if (ACTIVE == state)
    {
        this->setStyleSheet("background-color:green;");
        this->update();

        this->state = INACTIVE;
        this->setDisabled(false);
    }
}
