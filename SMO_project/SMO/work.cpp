/* TODO:
 * [X]Summing tProcessing with tLifeTime with Applications in buffer
 * [X]Comparing tLifeTime with tProcessing
 * [X]Add index of Application
 * [X]Record states of all applications
 * [X]Refactor main cycle
 * [X]Refactor output table formation
 * [ ]Optimize for more than 100 applications
 */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <QLabel>
#include "work.h"

std::vector<Application> generateApplicationsVector(const int &srcNum, const int &appNum, const double &l)
{
  srand(time(NULL));
  std::vector<Application> newAppVector;
  int appCount = 0;
  int s = 0;
  double newTime = 0.;
  while(appCount < appNum)
  {
    double r = double(rand())/RAND_MAX;
    newTime += -(1./l) * log(r);
    Application newApplication(newTime, s);
    newAppVector.push_back(newApplication);
    appCount++;
    s < (srcNum - 1) ? s++ : s = 0;
  }
  std::sort(newAppVector.begin(), newAppVector.end(),
            [](Application &app1, Application &app2) -> bool
  {
    return app1.getGenTime() < app2.getGenTime();
  });
  for(int i = 0; i < srcNum; i++)
  {
    int indexCounter = 0;
    for(auto &&a : newAppVector)
    {
      if(a.getSrcNum() == i)
      {
        a.setIndex(indexCounter);
        indexCounter++;
      }
    }
  }
  return newAppVector;
}

void startSmo(const int &srcNum, const int &bufSize, const int &devNum, const double &l, const int &a, const int &b, const int &appNum,
              StatisticsManager &stats, QProgressDialog *progressDialog)
{
  std::vector<Application> applications = generateApplicationsVector(srcNum, appNum, l);
  DeviceManager devices(devNum, a, b);
  Buffer buffer(bufSize);
  stats.updateRecord(applications);
  std::cout << "Applications generated" << std::endl;
  std::cout << "Buffer initialized" << std::endl;
  std::cout << "Devices initialized" << std::endl;
  std::vector<Application>::iterator appIterator = applications.begin();
  while(!stats.isEnd(appNum))
  {
    if(progressDialog->wasCanceled())
    {
      break;
    }
    progressDialog->setLabelText("Simulation in progress...\nApplications left: " + QString::number(appNum - stats.getRejectedCount() - stats.getProcessedCount()));
    if(appIterator != applications.end())
    {
      buffer.tryToAddApplicationPtr(&*appIterator);
      appIterator++;
      stats.updateRecord(applications);
    }
    if(!buffer.isEmpty())
    {
      Application *expectedApplicationPtr = buffer.getExpectedApplicationPtr();
      Device *expectedDevicePtr = devices.getExpectedDevice(expectedApplicationPtr);
      if(expectedDevicePtr != nullptr)
      {
        buffer.popThisApplicationPtr(expectedApplicationPtr);
        devices.setApplicationPtr(expectedDevicePtr, expectedApplicationPtr);
        stats.updateRecord(applications);
      }
      expectedDevicePtr->~Device();
      expectedApplicationPtr->~Application();
    }
    else
    {
      devices.releaseAllApplications();
      stats.updateRecord(applications);
    }
  }
  stats.pushDevices(devices);
  std::cout << "------------------\nSimulation ended" << std::endl;
}
