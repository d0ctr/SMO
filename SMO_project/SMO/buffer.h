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
  double tryToAddApplicationPtr(Application *appPtr);
  bool isEmpty();
  void refactorBuffer();
  BufferCell *getExpectedApplicationBufferCellPtr();
  Application *getExpectedApplicationPtr();
  void popThisApplicationPtr(const Application *appPtr);
  void printBufferState();
  bool isFull();
  int getSourcePackage();
private:
  std::list<BufferCell> bufferList;
  int sourcePackage;
  int bufSize;
};

#endif // BUFFER_H
