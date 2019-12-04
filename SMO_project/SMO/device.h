#ifndef DEVICE_H
#define DEVICE_H
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "application.h"
#include "buffer.h"

class Device
{
public:
  Device() = default;
  ~Device() = default;
  Device(const int &index, const int &a, const int &b);
  void setApplicationPtr(Application *appPtr);
  bool isEmpty();
  void genProcessingTime();
  Application *popApplicationPtr();
  double getProcessingTime();
  int getIndex() const;
  Application *getApplicationPtr();
  int getAppCount();
  double getTimeCount();
  double getReleaseTime();
private:
  int index;
  double tProcessing;
  double tRelease;
  int appCount;
  double timeCount;
  Application *appPtr;
  bool empty;
  int a, b;
};

#endif // DEVICE_H
