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
    ui->buttonResults->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonStart_clicked()
{
  ui->buttonResults->setEnabled(false);
  QString srcNumstr = ui->lineNumOfSources->text();
  QString bufSizestr = ui->lineBufSize->text();
  QString devNumstr = ui->lineNumOfDevices->text();
  QString appNumstr = ui->lineNumOfApps->text();
  QString lstr = ui->lineLyambda->text();
  try {
    int srcNum = srcNumstr.toInt();
    int bufSize = bufSizestr.toInt();
    int devNum = devNumstr.toInt();
    int appNum = appNumstr.toInt();
    int l = lstr.toInt();
    QProgressDialog *progressDialog = new QProgressDialog("Simulation in progress...", "&Cancel", 0, appNum);
    StatisticsManager smoStats = StatisticsManager(ui->tableOutput, appNum, progressDialog);
    ui->tableOutput->setEnabled(0);
    progressDialog->setMinimumDuration(0);
    progressDialog->setWindowTitle("Please wait");
    startSmo(srcNum, bufSize, devNum, l, appNum, smoStats, progressDialog);
    progressDialog->setValue(appNum);
    ui->tableOutput->setEnabled(1);
    ui->buttonResults->setEnabled(true);
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

}

void MainWindow::on_buttonResults_clicked()
{
    ui->tableOutput->clear();
}


void MainWindow::on_pushButton_clicked()
{
    ui->tableOutput->setColumnCount(ui->tableOutput->columnCount() + 1);
}
