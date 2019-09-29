/* TODO:
 * [П]Summing tProcessing with tLifeTime with Applications in buffer
 * [И]Comparing tLifeTime with tProcessing
 * [З]Add index of Application
 * [Д]Record states of all applications
 * [Е]Refactor main cycle
 * [ ]Refactor output table formation
 */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "work.h"

std::vector<Application> generateApplicationsVector(const int &srcNum, const int &appNum, const int &l)
{
  srand(time(NULL));
  std::vector<Application> newAppVector;
  int appCount = 0;
  int s = 0;
  while(appCount < appNum)
  {
    double r = double(rand())/RAND_MAX;
    double newTime = -(1./l) * log(r);
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

void startSmo(const int &srcNum, const int &bufSize, const int &devNum, const int &l, const int &appNum, StatisticsManager &stats)
{
  std::vector<Application> applications = generateApplicationsVector(srcNum, appNum, l);
  DeviceManager devices(devNum, 1, 0);
  Buffer buffer(bufSize);
  stats.updateRecord(applications);
  std::cout << "Applications generated" << std::endl;
  //for(auto a : applications)
  //{
  //  std::cout << "Application <" << a.getSrcNum() << "." << a.getIndex() << "> with Gen time <" << a.getGenTime() << ">\n";
  //}a
  std::cout << "Buffer initialized" << std::endl;
  //buffer.printBufferState();
  std::cout << "Devices initialized" << std::endl;
  //devices.printDeviceState();
  std::vector<Application>::iterator appIterator = applications.begin();
  while(!stats.isEnd(appNum))
  {
    if(appIterator != applications.end())
    {
      buffer.tryToAddApplicationPtr(&*appIterator);
      appIterator++;
      stats.updateRecord(applications);
    }
    if(!buffer.isEmpty())
    {
      Device *expectedDevice = devices.getDevice();
      Application *expectedApplicationPtr = buffer.getExpectedApplicationPtr();
      if(expectedDevice->isEmpty() || expectedApplicationPtr->getLifeTime() >= expectedDevice->getProcessingTime())
      {
        buffer.popThisApplicationPtr(expectedApplicationPtr);
        devices.setApplicationPtr(expectedDevice, expectedApplicationPtr);
        stats.updateRecord(applications);
      }
      double tLifeToAdd = devices.getDevice()->getProcessingTime();
      buffer.updateLifeTime(tLifeToAdd);
      stats.updateRecord(applications);
    }
    else
    {
      devices.releaseAllApplications();
      stats.updateRecord(applications);
    }

  }
  stats.updateRecord(applications);
  std::cout << "------------------\nSimulation ended" << std::endl;
}
