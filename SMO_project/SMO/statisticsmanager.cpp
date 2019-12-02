#include "statisticsmanager.h"

StatisticsManager::StatisticsManager(int appCount, int devNum, int bufSize, int srcCount, QProgressDialog *progressDialog)
{
  iterationsCount = 0;
  this->devNum = devNum;
  this->bufSize = bufSize;
  this->appCount = appCount;
  this->progressDialog = progressDialog;
  this->srcCount = srcCount;
}

void StatisticsManager::updateRecord(std::vector<Application> appVector)
{
  iterationsRecord.push_back(appVector);
  iterationsCount++;
  processedCount = 0;
  rejectedCount = 0;
  for(auto a : appVector)
  {
    switch(a.getState())
    {
    case PROCESSED:
      processedCount++;
      break;
    case REJECTED:
      rejectedCount++; 
      break;
    default:
      break;
    }
  }
  progressDialog->setValue(getRejectedCount() + getProcessedCount());
  qApp->processEvents();
}
int StatisticsManager::getProcessedCount()
{
  return processedCount;
}
int StatisticsManager::getRejectedCount()
{
  return rejectedCount;
}
int StatisticsManager::getApplicationsCount()
{
  return appCount;
}
int StatisticsManager::getIterationsCount()
{
  return iterationsCount;
}
bool StatisticsManager::isEnd(const int &appNum)
{
  if(getRejectedCount() + getProcessedCount() == appNum)
  {
    return true;
  }
  return false;
}
void StatisticsManager::printStaticTables(QTableWidget *tableDevices, QTableWidget *tableSources)
{ 
  QStringList vHeaderListSources = QStringList();
  for(int i = 0; i < srcCount; i++)
  {
    vHeaderListSources << "Source " + QString::number(i + 1);

  }
  QStringList hHeaderListSources = QStringList();
  hHeaderListSources << "Generated" << "Processed" << "Rejected" << "Reject prob." << "Avrg. TIS" << "Avrg. TOW" << "Avrg. TOP" << "Disp. TOW" << "Disp. TOP"; // TOW - time of waitting, TIS - time in system, TOP - time of processing
  tableSources->setRowCount(srcCount);
  tableSources->setColumnCount(9);
  tableSources->setVerticalHeaderLabels(vHeaderListSources);
  tableSources->setHorizontalHeaderLabels(hHeaderListSources);

  QStringList vHeaderListDevices = QStringList();
  for(int i = 0; i < devNum; i++)
  {
    vHeaderListDevices << "Device " + QString::number(i + 1);
  }
  QStringList hHeaderListDevices = QStringList();
  hHeaderListDevices << "Efficiency";
  tableDevices->setColumnCount(1);
  tableDevices->setRowCount(devNum);
  tableDevices->setVerticalHeaderLabels(vHeaderListDevices);
  tableDevices->setHorizontalHeaderLabels(hHeaderListDevices);
  for(int i = 0; i < srcCount; i++)
  {
    std::vector<double> tOWVector, tOPVector;
    double tIS = 0, tOW = 0, tOP = 0;
    int genCount = 0, rejCount = 0;
    for(auto a : *&iterationsRecord.back())
    {
      if(a.getSrcNum() == i)
      {
        genCount++;
        tOWVector.push_back(a.getAwaittingTime());
        tOPVector.push_back(a.getProcessingTime());
        tOP += a.getProcessingTime();
        tOW += a.getAwaittingTime();
        tIS += a.getLifeTime();
        if(a.getState() == REJECTED)
        {
          rejCount++;
        }
      }
    }
    int proCount = genCount - rejCount;
    double x1 = 0, x2 = 0;
    for(auto v : tOWVector)
    {
      x1 += v;
      x2 += pow(v, 2);
    }
    x1 = pow(x1/proCount, 2);
    x2 = x2 / proCount;
    double dispTOW = x2 - x1;
    x1 = 0;
    x2 = 0;
    for(auto v : tOPVector)
    {
      x1 += v;
      x2 += pow(v, 2);
    }
    x1 = pow(x1/proCount, 2);
    x2 = x2 / proCount;
    double dispTOP = x2 - x1;


    QTableWidgetItem *genCountItem = new QTableWidgetItem;
    genCountItem->setText(QString::number(genCount));
    QTableWidgetItem *rejCountItem = new QTableWidgetItem;
    rejCountItem->setText(QString::number(rejCount));
    QTableWidgetItem *procCountItem = new QTableWidgetItem;
    procCountItem->setText(QString::number(proCount));
    QTableWidgetItem *rejProbItem = new QTableWidgetItem;
    rejProbItem->setText(QString::number(double(rejCount) / double (genCount)));
    QTableWidgetItem *dispTOWItem = new QTableWidgetItem;
    dispTOWItem->setText(QString::number(dispTOW));
    QTableWidgetItem *dispTOPItem = new QTableWidgetItem;
    dispTOPItem->setText(QString::number(dispTOP));
    QTableWidgetItem *tOPItem = new QTableWidgetItem;
    tOPItem->setText(QString::number(tOP));
    QTableWidgetItem *tOWItem = new QTableWidgetItem;
    tOWItem->setText(QString::number(tOW));
    QTableWidgetItem *tISItem = new QTableWidgetItem;
    tISItem->setText(QString::number(tIS));

    tableSources->setItem(i , 0, genCountItem);
    tableSources->setItem(i , 1, procCountItem);
    tableSources->setItem(i , 2, rejCountItem);
    tableSources->setItem(i , 3, rejProbItem);
    tableSources->setItem(i , 4, tISItem);
    tableSources->setItem(i , 5, tOWItem);
    tableSources->setItem(i , 6, tOPItem);
    tableSources->setItem(i , 7, dispTOWItem);
    tableSources->setItem(i , 8, dispTOPItem);

  }
  double tLastRelease = 0.;
  for(auto d : *devices.getDeviceVector())
  {
    if(d.getReleaseTime() > tLastRelease)
    {
      tLastRelease = d.getReleaseTime();
    }
  }
  double tSMOWork = tLastRelease - (iterationsRecord.back().front()).getGenTime();
  for(int i = 0; i < devNum; i++)
  {
    double timeCount = devices.getDeviceVector()->at(i).getTimeCount();
    QTableWidgetItem *efficiencyItem = new QTableWidgetItem;
    efficiencyItem->setText(QString::number((timeCount / tSMOWork) * 100) + QString('%'));
    tableDevices->setItem(i , 0, efficiencyItem);
  }
}
void StatisticsManager::pushDevices(DeviceManager devices)
{
  this->devices = devices;
}
