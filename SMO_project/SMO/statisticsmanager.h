#ifndef STATISTICSRECORDER_H
#define STATISTICSRECORDER_H
#include <vector>
#include <list>
#include <iostream>
#include <cmath>
#include <QTableWidget>
#include <QTextEdit>
#include <QString>
#include <QApplication>
#include <QProgressDialog>
#include <QMainWindow>
#include <QLineEdit>
#include "devicemanager.h"
#include "buffer.h"
#include "application.h"

class StatisticsManager
{
public:
  StatisticsManager() = default;
  ~StatisticsManager() = default;
  StatisticsManager(int appCount, int devNum, int bufSize, int srcCount, QProgressDialog *progressDialog,
                    QTableWidget *tableSources, QTableWidget *tableBuffer, QTableWidget *tableDevices, QTableWidget *tableRejected, QTableWidget *tableProcesed);
  void updateRecord(std::vector<Application> appVector, double systemTime);
  int getProcessedCount();
  int getRejectedCount();
  bool isEnd(const int &appCount);
  int getRecordCount();
  int getApplicationsCount();
  void updateStepMode(int recordNum, QTableWidget *tableSources, QTableWidget *tableBuffer, QTableWidget *tableDevices, QTableWidget *tableRejected, QTableWidget *tableProcesed,
                      QLineEdit *lineSystemTime, QLineEdit *lineOnStep, QLineEdit *lineAmountOfSteps);
  void printAutoMode(QTableWidget *tableDevices, QTableWidget *tableSources);
  void pushDevices(DeviceManager devices);
private:
  std::vector<std::vector<Application>> appVectorRecord;
  std::vector<DeviceManager> devicesRecord;
  std::vector<Buffer> bufferRecord;
  std::vector<double> systemTimeRecord;
  int recordCount;
  int processedCount;
  int rejectedCount;
  int appCount;
  int devNum;
  int bufSize;
  int srcCount;
  QProgressDialog *progressDialog;
  DeviceManager devices;
};

#endif // STATISTICSRECORDER_H
