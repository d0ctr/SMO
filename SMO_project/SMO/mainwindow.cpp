
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
    double a = aStr.toDouble();
    double b = bStr.toDouble();
    QProgressDialog *progressDialog = new QProgressDialog("Simulation in progress...", "&Cancel", 0, appNum);
    smoStats.~StatisticsManager();
    smoStats = StatisticsManager(appNum, devNum, bufSize, srcNum, progressDialog, ui->tableWidgetSources, ui->tableWidgetBuffer,
                                                   ui->tableWidgetDevices, ui->tableWidgetRejected, ui->tableWidgetProcessed);
    QWidget::setEnabled(0);
    progressDialog->resize(progressDialog->size() + QSize(50, 0));
    progressDialog->setMinimumDuration(0);
    progressDialog->setWindowTitle("Please wait");
    startSmo(srcNum, bufSize, devNum, l, a, b, appNum, smoStats, progressDialog);
    progressDialog->setValue(appNum);
    ui->horizontalScrollBarSteps->setValue(0);
    ui->horizontalScrollBarSteps->setMaximum(smoStats.getRecordCount() - 1);
    ui->horizontalScrollBarSteps->setEnabled(1);
    smoStats.printAutoMode(ui->tableDevicesStats, ui->tableSourcesStats);
    smoStats.updateStepMode(0, ui->tableWidgetSources, ui->tableWidgetBuffer, ui->tableWidgetDevices,
                            ui->tableWidgetRejected, ui->tableWidgetProcessed,
                            ui->lineEditSystemTime, ui->lineEditOnStep, ui->lineEditAmountOfSteps);
    QWidget::setEnabled(1);
    ui->tabWidget->setCurrentIndex(1);
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

}



void MainWindow::on_horizontalScrollBarSteps_sliderReleased()
{

}

void MainWindow::on_horizontalScrollBarSteps_valueChanged(int value)
{
  smoStats.updateStepMode(value, ui->tableWidgetSources, ui->tableWidgetBuffer, ui->tableWidgetDevices, ui->tableWidgetRejected, ui->tableWidgetProcessed,
                          ui->lineEditSystemTime, ui->lineEditOnStep, ui->lineEditAmountOfSteps);
}
