#ifndef STATISTICSRECORDER_H
#define STATISTICSRECORDER_H
#include <vector>
#include <list>
#include <QTableWidget>
#include <QTextEdit>
#include <QString>
#include <iostream>
#include "application.h"

class StatisticsManager
{
public:
  StatisticsManager() = default;
  void updateRecord(std::vector<Application> appVector);
  void buildTableOutput(QTableWidget *tableOutput, QTextEdit *log);
  int getProcessedNum(std::vector<Application> &appVector);
  int getRejectedNum(std::vector<Application> &appVector);
  bool isEnd(const int &appNum);
  int getIterationsNum();
  int getApplicationsNum();
private:
  std::list<std::vector<Application>> iterationsRecords;
};

#endif // STATISTICSRECORDER_H
