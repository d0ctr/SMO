#include "device.h"

Device::Device(const int &index, const int &a, const int &b)
{
  this->index = index;
  this->a = a;
  this->b = b;
  empty = true;
  tProcessing = 0.;
}
void Device::setApplicationPtr(Application *appPtr)
{
  this->appPtr = appPtr;
  genProcessingTime();
  appPtr->setProcessingTime(tProcessing);
  appPtr->setState(INDEV);
  empty = false;
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
  appPtr = nullptr;
  empty = true;
  appPtrToReturn->setState(PROCESSED);
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
