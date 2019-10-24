#ifndef STATISTICSRECORDER_H
#define STATISTICSRECORDER_H
#include <vector>
#include <list>
#include <iostream>
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
  StatisticsManager(QTableWidget *bufferTable, QTableWidget *deviceTable, QTableWidget *rejectedTable, QTableWidget *processedTable,
                    int appCount, int devNum, int bufSize, QProgressDialog *progressDialog);
  void updateRecord(std::vector<Application> appVector, Buffer &buffer, DeviceManager &devices);
  int getProcessedCount();
  int getRejectedCount();
  bool isEnd(const int &appCount);
  int getIterationsCount();
  int getApplicationsCount();
  void printStats(Buffer &buffer, DeviceManager &devices);
private:
  std::list<std::vector<Application>> iterationsRecord;
  int iterationsCount;
  int processedCount;
  int rejectedCount;
  int appCount;
  int devNum;
  int bufSize;
  QTableWidget *bufferTable;
  QTableWidget *deviceTable;
  QTableWidget *rejectedTable;
  QTableWidget *processedTable;
  QProgressDialog *progressDialog;
};

#endif // STATISTICSRECORDER_H
