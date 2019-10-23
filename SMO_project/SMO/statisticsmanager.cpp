#include "statisticsmanager.h"

StatisticsManager::StatisticsManager(QTableWidget *tableOutput, int appCount, QProgressDialog *progressDialog)
{
  tableOutputPtr = tableOutput;
  iterationsCount = 0;
  this->appCount = appCount;
  tableOutputPtr->setRowCount(appCount + 1);
  tableOutputPtr->setColumnCount(iterationsCount);
  tableOutputPtr->setColumnWidth(iterationsCount, 800);
  this->progressDialog = progressDialog;
}

void StatisticsManager::updateRecord(std::vector<Application> appVector)
{
  processedCount = 0;
  rejectedCount = 0;
  for(auto a : appVector)
  {
    if(a.getState() == PROCESSED)
    {
      processedCount++;
    }
    else if(a.getState() == REJECTED)
    {
      rejectedCount++;
    }
  }
  tableOutputPtr->setColumnCount(iterationsCount + 1);
  std::vector<Application>::iterator statsIterator = appVector.begin();
  for(int row = 0; statsIterator != appVector.end(); row++, statsIterator++)
  {
    QString cellContentText;
    cellContentText.append("Application <");
    cellContentText.append(QString::number(statsIterator->getSrcNum()));
    cellContentText.append(".");
    cellContentText.append(QString::number(statsIterator->getIndex()));
    cellContentText.append("> Gen time <");
    cellContentText.append(QString::number(statsIterator->getGenTime()));
    cellContentText.append("> Life time <");
    cellContentText.append(QString::number(statsIterator->getLifeTime()));
    cellContentText.append("> Processing time <");
    cellContentText.append(QString::number(statsIterator->getProcessingTime()));
    cellContentText.append("> ");
    switch(statsIterator->getState())
    {
    case PREGEN:
      cellContentText.append("in GENERATOR");
      break;
    case INBUF:
      cellContentText.append("in BUFFER");
      break;
    case INDEV:
      cellContentText.append("in DEVICE");
      break;
    case REJECTED:
      cellContentText.append("got REJECTED");
      break;
    case PROCESSED:
      cellContentText.append("got PROCESSED");
      break;
    default:
      break;
    }
    QTableWidgetItem *cellContent = new QTableWidgetItem;
    cellContent->setText(cellContentText);
    tableOutputPtr->setItem(row, iterationsCount, cellContent);
  }
  QString sum;
  sum.append("Rejected: ");
  sum.append(QString::number(getRejectedCount()));
  sum.append("\tProcessed: ");
  sum.append(QString::number(getProcessedCount()));
  QTableWidgetItem *cellContent = new QTableWidgetItem;
  cellContent->setText(sum);
  tableOutputPtr->setItem(appCount, iterationsCount, cellContent);
  for(int i = 0; i < tableOutputPtr->columnCount(); i++)
  {
    tableOutputPtr->setColumnWidth(i, 800);
  }
  iterationsCount++;
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
