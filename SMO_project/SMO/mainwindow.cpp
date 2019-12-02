#include <iostream>
#include <exception>
#include <QProgressDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "work.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonStart_clicked()
{
  QString srcNumStr = ui->lineNumOfSources->text();
  QString bufSizeStr = ui->lineBufSize->text();
  QString devNumStr = ui->lineNumOfDevices->text();
  QString appNumStr = ui->lineNumOfApps->text();
  QString lStr = ui->lineLyambda->text();
  QString aStr = ui->lineA->text();
  QString bStr = ui->lineB->text();
  try {
    int srcNum = srcNumStr.toInt();
    int bufSize = bufSizeStr.toInt();
    int devNum = devNumStr.toInt();
    int appNum = appNumStr.toInt();
    double l = lStr.toDouble();
    int a = aStr.toInt();
    int b = bStr.toInt();
    QProgressDialog *progressDialog = new QProgressDialog("Simulation in progress...", "&Cancel", 0, appNum);
    StatisticsManager smoStats = StatisticsManager(appNum, devNum, bufSize, srcNum, progressDialog);
    QWidget::setEnabled(0);
    progressDialog->resize(progressDialog->size() + QSize(50, 0));
    progressDialog->setMinimumDuration(0);
    progressDialog->setWindowTitle("Please wait");
    startSmo(srcNum, bufSize, devNum, l, a, b, appNum, smoStats, progressDialog);
    progressDialog->setValue(appNum);
    smoStats.printStaticTables(ui->tableDevicesStats, ui->tableSourcesStats);
    QWidget::setEnabled(1);
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

}


