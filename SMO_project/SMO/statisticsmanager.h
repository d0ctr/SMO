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
#include "application.h"

class StatisticsManager
{
public:
  StatisticsManager(QTableWidget *tableOutput, int appCount, QProgressDialog *progressDialog);
  void updateRecord(std::vector<Application> appVector);
  int getProcessedCount();
  int getRejectedCount();
  bool isEnd(const int &appCount);
  int getIterationsCount();
  int getApplicationsCount();
private:
  int iterationsCount;
  int processedCount;
  int rejectedCount;
  int appCount;
  QTableWidget *tableOutputPtr;
  QProgressDialog *progressDialog;
};

#endif // STATISTICSRECORDER_H
