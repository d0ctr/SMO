#include "statisticsmanager.h"

StatisticsManager::StatisticsManager(QTableWidget *bufferTable, QTableWidget *deviceTable, QTableWidget *rejectedTable, QTableWidget *processedTable,
                                     int appCount, int devNum, int bufSize, QProgressDialog *progressDialog)
{
  this->bufferTable = bufferTable;
  this->deviceTable = deviceTable;
  this->rejectedTable = rejectedTable;
  this->processedTable = processedTable;
  iterationsCount = 0;
  this->devNum = devNum;
  this->bufSize = bufSize;
  this->appCount = appCount;
  this->progressDialog = progressDialog;

  bufferTable->setColumnCount(1);
  bufferTable->setColumnWidth(0, 300);
  bufferTable->setRowCount(bufSize);
  bufferTable->setMaximumHeight((bufSize + 2) * bufferTable->rowHeight(bufSize - 1));

  deviceTable->setColumnCount(1);
  deviceTable->setColumnWidth(0, 300);
  deviceTable->setRowCount(devNum);
  deviceTable->setMaximumHeight((devNum + 2) * deviceTable->rowHeight(devNum - 1));

  rejectedTable->setColumnCount(1);
  processedTable->setColumnCount(1);
  processedTable->setColumnWidth(0, 300);
}

void StatisticsManager::updateRecord(std::vector<Application> appVector, Buffer &buffer, DeviceManager &devices)
{
  iterationsRecord.push_back(appVector);
  processedCount = 0;
  rejectedCount = 0;
  int bufPosition = 0;
  int devPosition = 0;
  QString cellContentText;
  QTableWidgetItem *cellContent;
  bufferTable->clear();
  deviceTable->clear();
  processedTable->clear();
  rejectedTable->clear();
  for(auto b : *buffer.getBufferList())
  {
    if(!b.isEmpty())
    {
      cellContent = new QTableWidgetItem;
      cellContentText = QString();
      cellContentText.append("App: ").append(QString::number(b.getApplicationPtr()->getSrcNum())).append(".")
          .append(QString::number(b.getApplicationPtr()->getIndex())).append(" Life: ").append(QString::number(b.getApplicationPtr()->getLifeTime()))
          .append(" Waitting: ").append(QString::number(b.getApplicationPtr()->getAwaittingTime()));
      cellContent->setText(cellContentText);
      bufferTable->setItem(b.getIndex(), 0, cellContent);
    }
    else
    {
      cellContent = new QTableWidgetItem;
      cellContentText = "EMPTY";
      cellContent->setText(cellContentText);
      bufferTable->setItem(b.getIndex(), 0, cellContent);
    }
  }
  for(auto d : *devices.getDeviceList())
  {
    if(!d.isEmpty())
    {
      cellContent = new QTableWidgetItem;
      cellContentText = QString();
      cellContentText.append("App: ").append(QString::number(d.getApplicationPtr()->getSrcNum())).append(".")
          .append(QString::number(d.getApplicationPtr()->getIndex())).append(" Life: ").append(QString::number(d.getApplicationPtr()->getLifeTime()))
          .append(" Processing: ").append(QString::number(d.getApplicationPtr()->getProcessingTime()));
      cellContent->setText(cellContentText);
      deviceTable->setItem(d.getIndex(), 0, cellContent);
    }
    else
    {
      cellContent = new QTableWidgetItem;
      cellContentText = "EMPTY";
      cellContent->setText(cellContentText);
      deviceTable->setItem(d.getIndex(), 0, cellContent);
    }
  }
  for(auto a : appVector)
  {
    switch(a.getState())
    {
    case PROCESSED:
      processedCount++;
      processedTable->setRowCount(processedCount);
      cellContent = new QTableWidgetItem;
      cellContentText = QString();
      cellContentText.append("App: ").append(QString::number(a.getSrcNum())).append(".").append(QString::number(a.getIndex()))
          .append(" Life: ").append(QString::number(a.getLifeTime()));
      cellContent->setText(cellContentText);
      processedTable->setItem(processedCount - 1, 0, cellContent);
      break;
    case REJECTED:
      rejectedCount++;
      rejectedTable->setRowCount(rejectedCount);
      cellContent = new QTableWidgetItem;
      cellContentText = QString();
      cellContentText.append("App: ").append(QString::number(a.getSrcNum())).append(".").append(QString::number(a.getIndex()));
      cellContent->setText(cellContentText);
      rejectedTable->setItem(rejectedCount - 1, 0, cellContent);
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
void StatisticsManager::printStats(Buffer &buffer, DeviceManager &devices)
{
  QString cellContentText;
  QTableWidgetItem *cellContent;
  for(auto d : *devices.getDeviceList())
  {
    cellContent = new QTableWidgetItem;
    cellContentText = QString();
    cellContentText.append("AppCount: ").append(QString::number(d.getAppCount())).append(" Average time: ")
        .append(QString::number(d.getTimeCount() / d.getAppCount()));
    cellContent->setText(cellContentText);
    deviceTable->setItem(d.getIndex(), 0, cellContent);
  }
}
