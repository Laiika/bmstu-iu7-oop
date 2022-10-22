#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "handler.h"

#define CV_WIDTH 1000
#define CV_HEIGHT 600

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    rc_t draw_result();

    void on_rotateButton_clicked();

    void on_moveButton_clicked();

    void on_scaleButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
