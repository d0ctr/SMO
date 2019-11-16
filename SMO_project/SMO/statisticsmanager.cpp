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
  hHeaderListSources << "Generated" << "Processed" << "Rejected" << "Rehect prob." << "Avrg. TIS" << "Disp. TOW" << "Disp. TOP"; // TOW - time of waitting, TIS - time in system, TOP - time of processing
  tableSources->setRowCount(srcCount);
  tableSources->setColumnCount(7);
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
}
void StatisticsManager::pushDevices(DeviceManager devices)
{
  this->devices = devices;
}
