#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    request_t req;
    req.command = END;
    request_handle(req);

    delete ui;
}


rc_t MainWindow::draw_result()
{
    canvas_t canvas;
    canvas.scene = ui->graphicsView->scene();
    canvas.height = ui->graphicsView->height();
    canvas.width = ui->graphicsView->width();

    request_t req;
    req.command = DRAW;
    req.canvas = canvas;

    return request_handle(req);
}


void MainWindow::on_loadButton_clicked()
{
    request_t req;
    req.command = LOAD;
    req.filename = "../lab1/test.txt";

    rc_t rc = request_handle(req);
    if (OK != rc)
    {
        error_print(rc);
        return;
    }

    rc = draw_result();
    if (OK != rc)
        error_print(rc);
}


void MainWindow::on_rotateButton_clicked()
{
    coeffs_t coeffs;
    coeffs.x = ui->rotateX->value();
    coeffs.y = ui->rotateY->value();
    coeffs.z = ui->rotateZ->value();

    point_t center;
    center.x = ui->xc->value();
    center.y = ui->yc->value();
    center.z = ui->zc->value();

    request_t req;
    req.command = ROTATE;
    req.coeffs = coeffs;
    req.center = center;

    rc_t rc = request_handle(req);
    if (OK != rc)
    {
        error_print(rc);
        return;
    }

    rc = draw_result();
    if (OK != rc)
        error_print(rc);
}


void MainWindow::on_moveButton_clicked()
{
    coeffs_t coeffs;
    coeffs.x = ui->dx->value();
    coeffs.y = ui->dy->value();
    coeffs.z = ui->dz->value();

    request_t req;
    req.command = MOVE;
    req.coeffs = coeffs;

    rc_t rc = request_handle(req);
    if (OK != rc)
    {
        error_print(rc);
        return;
    }

    rc = draw_result();
    if (OK != rc)
        error_print(rc);
}


void MainWindow::on_scaleButton_clicked()
{
    coeffs_t coeffs;
    coeffs.x = ui->kx->value();
    coeffs.y = ui->ky->value();
    coeffs.z = ui->kz->value();

    point_t center;
    center.x = ui->xc->value();
    center.y = ui->yc->value();
    center.z = ui->zc->value();

    request_t req;
    req.command = SCALE;
    req.coeffs = coeffs;
    req.center = center;

    rc_t rc = request_handle(req);
    if (OK != rc)
    {
        error_print(rc);
        return;
    }

    rc = draw_result();
    if (OK != rc)
        error_print(rc);
}

