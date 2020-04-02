#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <exception>
#include <QMainWindow>
#include <QProgressDialog>
#include <QScrollEvent>
#include "statisticsmanager.h"

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
    void on_buttonStart_clicked();

    void on_horizontalScrollBarSteps_sliderReleased();

    void on_horizontalScrollBarSteps_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    StatisticsManager smoStats;

};
#endif // MAINWINDOW_H
