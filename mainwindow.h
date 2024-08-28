#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "solver.h"

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
    void on_btn_run_clicked();
    void on_x0_editingFinished();
    void on_y0_editingFinished();

private:
    Ui::MainWindow *ui;
    double calculateLenght();
};
#endif // MAINWINDOW_H
