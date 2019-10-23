#ifndef WORK_H
#define WORK_H

#include <vector>
#include <QProgressDialog>
#include "buffer.h"
#include "devicemanager.h"
#include "statisticsmanager.h"

std::vector<Application> generateApplicationsVector(const int &srcNum, const int &appNum, const int &l);
void startSmo(const int &srcNum, const int &bufSize, const int &devNum, const int &l, const int &appNum, StatisticsManager &startSmo, QProgressDialog *progressDialog);
#endif // WORK_H
