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

Device *DeviceManager::getDevice()
{
  Device *devWithMinProcessingTime = &devList.front();
  for(auto &&d : devList)
  {
    if(d.isEmpty())
    {
      return &d;
    }
    else if(d.getApplicationPtr()->getLifeTime() < devWithMinProcessingTime->getApplicationPtr()->getLifeTime())
    {
      devWithMinProcessingTime = &d;
    }
  }
  return devWithMinProcessingTime;
}
void DeviceManager::setApplicationPtr(Device *device, Application *appPtr)
{
  if(!device->isEmpty())
  {
    device->popApplicationPtr();
  }
  device->setApplicationPtr(appPtr);
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
