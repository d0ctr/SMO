#include "devicemanager.h"

DeviceManager::DeviceManager(const int &devNum, const int &a, const int &b)
{
  this->devNum = devNum;
  for(int i = 0; i < devNum; i++)
  {
    Device newDevice(i, a, b);
    devVector.push_back(newDevice);
  }

}
bool DeviceManager::isEmpty()
{
  for(auto &d : devVector)
  {
    if(!d.isEmpty())
    {
      return false;
    }
  }
  return true;
}

void DeviceManager::releaseApplicationsByTime(double &systemTime)
{
  for(auto &d : devVector)
  {
    d.releaseByTime(systemTime);
  }
}

Device *DeviceManager::getExpectedDevice(double systemTime)
{
  Device *devWithMinReleaseTime = &devVector.front();
  for(auto &d : devVector)
  {
    if(d.getReleaseTime() < devWithMinReleaseTime->getReleaseTime() && !d.isEmpty())
    {
      devWithMinReleaseTime = &d;
    }
  }
  if(devWithMinReleaseTime->getReleaseTime() <= systemTime)
  {
    return devWithMinReleaseTime;
  }
  for(auto &d : devVector)
  {
    if(d.isEmpty())
    {
      return &d;
    }
  }
  return nullptr;
}

void DeviceManager::setApplicationPtr(Device *devicePtr, Application *appPtr)
{
  if(!devicePtr->isEmpty())
  {
    devicePtr->popApplicationPtr();
  }
  devicePtr->setApplicationPtr(appPtr);
}
void DeviceManager::releaseAllApplications()
{
  for(auto &&d : devVector)
  {
    if(!d.isEmpty())
    {
      d.popApplicationPtr();
    }
  }
}

void DeviceManager::printDeviceState()
{
  for(auto &&d : devVector)
  {
    if(!d.isEmpty())
    {
      std::cout << "Device <" << d.getIndex() << "> will release in <" << d.getReleaseTime() << "> with Application <"
                << d.getApplicationPtr()->getSrcNum() << "." << d.getApplicationPtr()->getIndex() << std::endl;
    }
    else
    {
      std::cout << "Device <" << d.getIndex() << "> is empty" << std::endl;
    }
  }
}

std::vector<Device> *DeviceManager::getDeviceVector()
{
  return &devVector;
}

bool DeviceManager::isFull()
{
  for(auto &&d : devVector)
  {
    if(d.isEmpty())
    {
      return false;
    }
  }
  return true;
}

