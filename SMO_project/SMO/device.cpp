#include "device.h"

Device::Device(const int &index, const int &a, const int &b)
{
  appPtr = nullptr;
  this->index = index;
  this->a = a;
  this->b = b;
  empty = true;
  tProcessing = 0.;
  tRelease = 0.;
  appCount = 0;
  timeCount = 0.;
}
void Device::setApplicationPtr(Application *appPtr)
{
  double tEntry = getReleaseTime();
  appPtr->setAwaittingTime(tEntry);
  this->appPtr = appPtr;
  genProcessingTime();
  appPtr->setProcessingTime(tProcessing);
  appPtr->setState(INDEV);
  appPtr->setDeviceIndex(index);
  this->tRelease = appPtr->getReleaseTime();
  empty = false;
  appCount++;
  timeCount += getProcessingTime();
}
bool Device::isEmpty()
{
  return empty;
}
void Device::genProcessingTime()
{
  tProcessing = double(rand()) / RAND_MAX * (b - a) + a;
}
Application *Device::popApplicationPtr()
{
  Application *appPtrToReturn = appPtr;
  if(appPtr != nullptr)
  {
    appPtr = nullptr;
    empty = true;
    tProcessing = 0;
    appPtrToReturn->setState(PROCESSED);
  }
  return appPtrToReturn;
}
double Device::getProcessingTime()
{
  return tProcessing;
}
int Device::getIndex() const
{
  return index;
}
Application *Device::getApplicationPtr()
{
  return appPtr;
}
int Device::getAppCount()
{
  return appCount;
}
double Device::getTimeCount()
{
  return timeCount;
}
double Device::getReleaseTime()
{
  return tRelease;
}
void Device::releaseByTime(double &systemTime)
{
  if(!isEmpty())
  {
    if(tRelease <= systemTime)
    {
      popApplicationPtr();
    }
  }
}
