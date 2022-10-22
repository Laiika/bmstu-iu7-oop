#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QObject>


class Button : public QPushButton
{
    Q_OBJECT;

    enum ButtonStates
    {
        ACTIVE,
        INACTIVE
    };

public:
    Button(QWidget *parent = nullptr);
    ~Button() = default;

    void set_floor(const int &floor);

// вырабатывается, когда происходит событие
signals:
    void signal_press(int floor);
    void signal_unpress();

// вызывается в ответ на определенный сигнал
public slots:
    void slot_unpress();

private:
    ButtonStates state;
    int floor;

private slots:
    void slot_press();
};

#endif // BUTTON_H
