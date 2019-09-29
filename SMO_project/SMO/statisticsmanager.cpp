#include "statisticsmanager.h"

void StatisticsManager::updateRecord(std::vector<Application> appVector)
{
  iterationsRecords.push_back(appVector);
}
int StatisticsManager::getProcessedNum(std::vector<Application> &appVector)
{
  int processedNum = 0;
  for(auto a : appVector)
  {
    if(a.getState() == PROCESSED)
    {
      processedNum++;
    }
  }
  return processedNum;
}
int StatisticsManager::getRejectedNum(std::vector<Application> &appVector)
{
  int rejectedNum = 0;
  for(auto &&a : appVector)
  {
    if(a.getState() == REJECTED)
    {
      rejectedNum++;
    }
  }
  return rejectedNum;
}
int StatisticsManager::getApplicationsNum()
{
  return iterationsRecords.back().size();
}
int StatisticsManager::getIterationsNum()
{
  return iterationsRecords.size();
}
bool StatisticsManager::isEnd(const int &appNum)
{
  if(getRejectedNum(iterationsRecords.back()) + getProcessedNum(iterationsRecords.back()) == appNum)
  {
    return true;
  }
  return false;
}
void StatisticsManager::buildTableOutput(QTableWidget *tableOutput, QTextEdit *log)
{
  tableOutput->setRowCount(getApplicationsNum()+1);
  tableOutput->setColumnCount(getIterationsNum());
  std::list<std::vector<Application>>::iterator statsIterator = iterationsRecords.begin();
  for(int column = 0; statsIterator != iterationsRecords.end(); column++, statsIterator++)
  {
    tableOutput->setColumnWidth(column, 800);
    std::vector<Application>::iterator appIterator = statsIterator->begin();
    for(int row = 0; appIterator!=statsIterator->end(); row++, appIterator++ )
    {
      QString cellContentText;
      cellContentText.append("Application <");
      cellContentText.append(QString::number(appIterator->getSrcNum()));
      cellContentText.append(".");
      cellContentText.append(QString::number(appIterator->getIndex()));
      cellContentText.append("> Gen time <");
      cellContentText.append(QString::number(appIterator->getGenTime()));
      cellContentText.append("> Life time <");
      cellContentText.append(QString::number(appIterator->getLifeTime()));
      cellContentText.append("> Processing time <");
      cellContentText.append(QString::number(appIterator->getProcessingTime()));
      cellContentText.append("> ");
      switch(appIterator->getState())
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
      tableOutput->setItem(row, column, cellContent);
    }

    QString sum;
    sum.append("Rejected: ");
    sum.append(QString::number(getRejectedNum(*statsIterator)));
    sum.append("\tProcessed: ");
    sum.append(QString::number(getProcessedNum(*statsIterator)));
    QTableWidgetItem *cellContent = new QTableWidgetItem;
    cellContent->setText(sum);
    tableOutput->setItem(tableOutput->rowCount() - 1, column, cellContent);
  }
}
