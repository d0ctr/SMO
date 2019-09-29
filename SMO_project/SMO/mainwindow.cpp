#include <iostream>
#include <exception>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    smoStats = StatisticsManager();
    startSmo(srcNum, bufSize, devNum, l, appNum, smoStats);
    ui->buttonResults->setEnabled(true);
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

}

void MainWindow::on_buttonResults_clicked()
{
    smoStats.buildTableOutput(ui->tableOutput, ui->textEdit);
}
