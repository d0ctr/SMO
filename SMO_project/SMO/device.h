#ifndef DEVICE_H
#define DEVICE_H
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "application.h"

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
private:
  int index;
  double tProcessing;
  Application *appPtr;
  bool empty;
  int a, b;
};

#endif // DEVICE_H
