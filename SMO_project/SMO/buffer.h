#ifndef BUFFER_H
#define BUFFER_H
#include <list>
#include <iostream>
#include "buffercell.h"

class Buffer
{
public:
  Buffer() = default;
  ~Buffer() = default;
  Buffer(const int &bufSize);
  std::list<BufferCell> *getBufferList();
  bool tryToAddApplicationPtr(Application *appPtr);
  bool isEmpty();
  void refactorBuffer();
  Application *getExpectedApplicationPtr();
  void popThisApplicationPtr(const Application *appPtr);
  void printBufferState();
  void updateLifeTime(double &tLifeToAdd);
private:
  std::list<BufferCell> bufferList;
  int sourcePackage;
  int bufSize;
};

#endif // BUFFER_H
