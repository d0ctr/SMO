#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H
#include <vector>
#include <iostream>
#include "device.h"

class DeviceManager
{
public:
  DeviceManager() = default;
  ~DeviceManager() = default;
  DeviceManager(const int &devNum, const int &a, const int &b);
  bool isEmpty();
  Device *getExpectedDevice(double systemTime);
  std::vector<Device> *getDeviceVector();
  void releaseApplicationsByTime(double &systemime);
  void releaseAllApplications();
  void setApplicationPtr(Device *devicePtr, Application *appPtr);
  void printDeviceState();
  bool isFull();
private:
  std::vector<Device> devVector;
  int devNum;
};

#endif // DEVICEMANAGER_H
