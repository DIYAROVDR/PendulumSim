#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solver.h"
#include <QVector>
#include <cmath>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Включаем масштабирование и перемещение графика
    ui->plot->setInteraction(QCP::iRangeZoom, true);
    ui->plot->setInteraction(QCP::iRangeDrag, true);

    // Настраиваем оси
    ui->plot->xAxis->setLabel("Время, с");
    ui->plot->yAxis->setLabel("Функция S(t), м");
    ui->plot->xAxis->setRange(0, 100);
    ui->plot->yAxis->setRange(0, 25);

    // Включаем видимую сетку на графике
    ui->plot->xAxis->grid()->setVisible(true);
    ui->plot->yAxis->grid()->setVisible(true);

    // Дополнительная сетка (разбиение осей)
    ui->plot->xAxis->grid()->setSubGridVisible(true);
    ui->plot->yAxis->grid()->setSubGridVisible(true);

    // Настройка цветовой гаммы сетки
    ui->plot->xAxis->grid()->setPen(QPen(Qt::gray));
    ui->plot->yAxis->grid()->setPen(QPen(Qt::gray));
    ui->plot->xAxis->grid()->setSubGridPen(QPen(Qt::lightGray));
    ui->plot->yAxis->grid()->setSubGridPen(QPen(Qt::lightGray));

    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::red));
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, 5));

    // Обновляем график
    ui->plot->replot();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btn_run_clicked() {
    double dt = ui->dt->text().toDouble();
    double x0 = ui->x0->text().toDouble();
    double y0 = ui->y0->text().toDouble();
    double v0 = ui->v0->text().toDouble();
    double m = ui->m->text().toDouble();
    double L = ui->L->text().toDouble();
    double t1 = ui->t1->text().toDouble();
    double t2 = ui->t2->text().toDouble();

    Solver s(m, L, x0, y0, v0);
    s.setTimeInterval(t1, t2, dt); // Устанавливаем временной интервал
    s.run(); // Запускаем расчет

    std::vector<double> x_tran = s.X();
    std::vector<double> y_tran = s.Y();

    QVector<double> x_values = QVector<double>(y_tran.begin(),y_tran.end());
    QVector<double> y_values = QVector<double>(y_tran.begin(),y_tran.end());

    // Создаем вектор времени
    QVector<double> t_values(x_values.size());
    for (int i = 0; i < t_values.size(); ++i) {
        t_values[i] = i * dt; // Шаг времени dt
    }

    // Рассчитываем значения S(t) = sqrt(x(t)^2 + y(t)^2)
    QVector<double> s_values(x_values.size());
    for (int i = 0; i < s_values.size(); ++i) {
        s_values[i] = std::sqrt(x_values[i] * x_values[i] + y_values[i] * y_values[i]);
    }

    ui->plot->addGraph();
    ui->plot->graph(0)->setData(t_values, s_values);
    ui->plot->rescaleAxes();
    ui->plot->replot();
}

void MainWindow::on_x0_editingFinished() {
    ui->L->setText(QString::number(calculateLenght()));
}


void MainWindow::on_y0_editingFinished() {
    ui->L->setText(QString::number(calculateLenght()));
}

double MainWindow::calculateLenght() {
    double y0 = ui->y0->text().toDouble();
    double x0 = ui->x0->text().toDouble();
    return sqrt(y0*y0+x0*x0);
}

