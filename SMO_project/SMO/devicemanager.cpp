#include "devicemanager.h"

DeviceManager::DeviceManager(const int &devNum, const int &a, const int &b)
{
  this->devNum = devNum;
  for(int i = 0; i < devNum; i++)
  {
    Device newDevice(i, a, b);
    devList.push_back(newDevice);
  }

}
bool DeviceManager::isEmpty()
{
  for(auto &&d : devList)
  {
    if(!d.isEmpty())
    {
      return false;
    }
  }
  return true;
}

Device *DeviceManager::getExpectedDevice(Application *appPtr)
{
  Device *devWithMinProcessingTime = &devList.front();
  for(auto &d : devList)
  {
    if(d.getProcessingTime() < devWithMinProcessingTime->getProcessingTime())
    {
      devWithMinProcessingTime = &d;
    }
  }
  if(devWithMinProcessingTime->getProcessingTime() <= appPtr->getGenTime())
  {
    return devWithMinProcessingTime;
  }
  for(auto &d : devList)
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
  for(auto &&d : devList)
  {
    if(!d.isEmpty())
    {
      d.popApplicationPtr();
    }
  }
}
void DeviceManager::printDeviceState()
{
  for(auto &&d : devList)
  {
    if(!d.isEmpty())
    {
      std::cout << "Device <" << d.getIndex() << "> is busy for <" << d.getProcessingTime() << "> with Application <"
                << d.getApplicationPtr()->getSrcNum() << "." << d.getApplicationPtr()->getIndex() << ">\n";
    }
    else
    {
      std::cout << "Device <" << d.getIndex() << "> is empty\n";
    }
  }
}
std::list<Device> *DeviceManager::getDeviceList()
{
  return &devList;
}
