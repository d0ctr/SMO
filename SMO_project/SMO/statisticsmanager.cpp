#include "statisticsmanager.h"

StatisticsManager::StatisticsManager(int appCount, int devNum, int bufSize, int srcCount, QProgressDialog *progressDialog,
                                     QTableWidget *tableSources, QTableWidget *tableBuffer, QTableWidget *tableDevices, QTableWidget *tableRejected, QTableWidget *tableProcesed)
{
  recordCount = 0;
  this->devNum = devNum;
  this->bufSize = bufSize;
  this->appCount = appCount;
  this->progressDialog = progressDialog;
  this->srcCount = srcCount;

  QStringList vHeaderList = QStringList();
  for(int i = 0; i < srcCount; i++)
  {
    vHeaderList << "Source " + QString::number(i + 1);

  }
  QStringList hHeaderList = QStringList();
  hHeaderList << "Application";
  tableSources->setRowCount(srcCount);
  tableSources->setColumnCount(1);
  tableSources->setVerticalHeaderLabels(vHeaderList);
  tableSources->setHorizontalHeaderLabels(hHeaderList);

  vHeaderList = QStringList();
  for(int i = 0; i < bufSize; i++)
  {
    vHeaderList << "Cell " + QString::number(i + 1);

  }
  hHeaderList = QStringList();
  hHeaderList << "Application";
  tableBuffer->setRowCount(bufSize);
  tableBuffer->setColumnCount(1);
  tableBuffer->setVerticalHeaderLabels(vHeaderList);
  tableBuffer->setHorizontalHeaderLabels(hHeaderList);

  vHeaderList = QStringList();
  for(int i = 0; i < devNum; i++)
  {
    vHeaderList << "Device " + QString::number(i + 1);
  }
  hHeaderList = QStringList();
  hHeaderList << "Application";
  tableDevices->setRowCount(devNum);
  tableDevices->setColumnCount(1);
  tableDevices->setVerticalHeaderLabels(vHeaderList);
  tableDevices->setHorizontalHeaderLabels(hHeaderList);

  hHeaderList = QStringList();
  hHeaderList << "Application";
  tableRejected->setColumnCount(1);
  tableRejected->setHorizontalHeaderLabels(hHeaderList);

  hHeaderList = QStringList();
  hHeaderList << "Application";
  tableProcesed->setColumnCount(1);
  tableProcesed->setHorizontalHeaderLabels(hHeaderList);
}

void StatisticsManager::updateRecord(std::vector<Application> appVector, double systemTime)
{
  appVectorRecord.push_back(appVector);
  systemTimeRecord.push_back(systemTime);
  recordCount++;
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
int StatisticsManager::getRecordCount()
{
  return recordCount;
}
bool StatisticsManager::isEnd(const int &appNum)
{
  if(getRejectedCount() + getProcessedCount() == appNum)
  {
    return true;
  }
  return false;
}
void StatisticsManager::updateStepMode(int recordNum, QTableWidget *tableSources, QTableWidget *tableBuffer, QTableWidget *tableDevices, QTableWidget *tableRejected, QTableWidget *tableProcesed,
                                       QLineEdit *lineSystemTime, QLineEdit *lineOnStep, QLineEdit *lineAmountOfSteps)
{
  std::vector<Application> *realAppVector = &appVectorRecord[size_t(recordNum)];
  std::vector<Application> realBuffer;
  std::vector<Application> realDevices;
  std::vector<Application> realProcessedVector;
  std::vector<Application> realRejectedVector;
  int realRejectedCount = 0;
  int realProcessedCount = 0;
  lineSystemTime->setText(QString::number(systemTimeRecord[size_t(recordNum)]));
  lineOnStep->setText(QString::number(recordNum + 1));
  lineAmountOfSteps->setText(QString::number(recordCount));
  tableSources->clearContents();
  tableBuffer->clearContents();
  tableDevices->clearContents();
  tableRejected->clearContents();
  tableProcesed->clearContents();
  for(auto a : *realAppVector)
  {
    switch(a.getState())
    {
      case PROCESSED:
        realProcessedCount++;
        realProcessedVector.push_back(a);
        break;
      case REJECTED:
        realRejectedCount++;
        realRejectedVector.push_back(a);
        break;
      case INBUF:
        realBuffer.push_back(a);
        break;
      case INDEV:
        realDevices.push_back(a);
        break;
      default:
        break;

    }
  }

  for(int i = 0; size_t(i) < realBuffer.size(); i++)
  {
    QString str = "<" + QString::number(realBuffer[size_t(i)].getSrcNum() + 1) + ", " + QString::number(realBuffer[size_t(i)].getIndex() + 1) +
        "> with gen time: " + QString::number(realBuffer[size_t(i)].getGenTime());
    QTableWidgetItem *cellItem = new QTableWidgetItem;
    cellItem->setText(str);
    tableBuffer->setItem(realBuffer[size_t(i)].getBufferCellIndex(), 0, cellItem);
  }

  for(int i = 0; size_t(i) < realDevices.size(); i++)
  {
    QString str = "<" + QString::number(realDevices[size_t(i)].getSrcNum() + 1) + ", " + QString::number(realDevices[size_t(i)].getIndex() + 1) +
        "> will exit at: " + QString::number(realDevices[size_t(i)].getReleaseTime());
    QTableWidgetItem *cellItem = new QTableWidgetItem;
    cellItem->setText(str);
    tableDevices->setItem(realDevices[size_t(i)].getDeviceIndex(), 0, cellItem);
  }

  for(auto &a : *realAppVector)
  {
    if(a.getState() == PREGEN)
    {
      QString str = "New app at: " + QString::number(a.getGenTime());
      QTableWidgetItem *cellItem = new QTableWidgetItem;
      cellItem->setText(str);
      tableSources->setItem(a.getSrcNum(), 0, cellItem);
      break;
    }
  }

  tableRejected->setRowCount(realRejectedCount);
  for(int i = 0; i < realRejectedCount; i++)
  {
    QString str = "<" + QString::number(realRejectedVector[size_t(i)].getSrcNum() + 1) + ", " + QString::number(realRejectedVector[size_t(i)].getIndex() + 1) + ">";
    QTableWidgetItem *cellItem = new QTableWidgetItem;
    cellItem->setText(str);
    tableRejected->setItem(i, 0, cellItem);
  }

  tableProcesed->setRowCount(realProcessedCount);
  for(int i = 0; i < realProcessedCount; i++)
  {
    QString str = "<" + QString::number(realProcessedVector[size_t(i)].getSrcNum() + 1) + ", "
        + QString::number(realProcessedVector[size_t(i)].getIndex() + 1) + "> released at: " + QString::number(realProcessedVector[size_t(i)].getReleaseTime());
    QTableWidgetItem *cellItem = new QTableWidgetItem;
    cellItem->setText(str);
    tableProcesed->setItem(i, 0, cellItem);
  }
}
void StatisticsManager::printAutoMode(QTableWidget *tableDevices, QTableWidget *tableSources)
{ 
  QStringList vHeaderListSources = QStringList();
  for(int i = 0; i < srcCount; i++)
  {
    vHeaderListSources << "Source " + QString::number(i + 1);

  }
  vHeaderListSources << "All sources";
  QStringList hHeaderListSources = QStringList();
  hHeaderListSources << "Generated" << "Processed" << "Rejected" << "Reject prob." << "Avrg. TIS" << "Avrg. TOW" << "Avrg. TOP" << "Disp. TOW" << "Disp. TOP"; // TOW - time of waitting, TIS - time in system, TOP - time of processing
  tableSources->setRowCount(srcCount + 1);
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
    for(auto a : *&appVectorRecord.back())
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

  std::vector<double> tOWVector, tOPVector;
  double tIS = 0, tOW = 0, tOP = 0;
  int genCount = 0, rejCount = 0;
  for(auto a : *&appVectorRecord.back())
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

  tableSources->setItem(srcCount, 0, genCountItem);
  tableSources->setItem(srcCount, 1, procCountItem);
  tableSources->setItem(srcCount, 2, rejCountItem);
  tableSources->setItem(srcCount, 3, rejProbItem);
  tableSources->setItem(srcCount, 4, tISItem);
  tableSources->setItem(srcCount, 5, tOWItem);
  tableSources->setItem(srcCount, 6, tOPItem);
  tableSources->setItem(srcCount, 7, dispTOWItem);
  tableSources->setItem(srcCount, 8, dispTOPItem);
  double tLastRelease = 0.;
  for(auto d : *devices.getDeviceVector())
  {
    if(d.getReleaseTime() > tLastRelease)
    {
      tLastRelease = d.getReleaseTime();
    }
  }
  double tSMOWork = tLastRelease - (appVectorRecord.back().front()).getGenTime();
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
