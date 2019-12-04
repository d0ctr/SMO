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
#include "devicemanager.h"
#include "buffer.h"
#include "application.h"

class StatisticsManager
{
public:
  StatisticsManager(int appCount, int devNum, int bufSize, int srcCount, QProgressDialog *progressDialog);
  void updateRecord(std::vector<Application> appVector);
  int getProcessedCount();
  int getRejectedCount();
  bool isEnd(const int &appCount);
  int getIterationsCount();
  int getApplicationsCount();
  void printStaticTables(QTableWidget *tableDevices, QTableWidget *tableSources);
  void pushDevices(DeviceManager devices);
private:
  std::list<std::vector<Application>> iterationsRecord;
  int iterationsCount;
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
