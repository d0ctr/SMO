#ifndef WORK_H
#define WORK_H

#include <vector>
#include <QProgressDialog>
#include "buffer.h"
#include "devicemanager.h"
#include "statisticsmanager.h"

std::vector<Application> generateApplicationsVector(const int &srcNum, const int &appNum, const double &l);
void startSmo(const int &srcNum, const int &bufSize, const int &devNum, const double &l, const double &a, const double &b, const int &appNum,
              StatisticsManager &stats, QProgressDialog *progressDialog);
#endif // WORK_H
