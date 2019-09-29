#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include <list>
#include <iostream>
#include "device.h"

class DeviceManager
{
public:
  DeviceManager() = default;
  ~DeviceManager() = default;
  DeviceManager(const int &devNum, const int &a, const int &b);
  bool isEmpty();
  Device *getDevice();
  void releaseAllApplications();
  void setApplicationPtr(Device *device, Application *appPtr);
  void printDeviceState();
private:
  std::list<Device> devList;
  int devNum;
};

#endif // DEVICEMANAGER_H
