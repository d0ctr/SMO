#ifndef BUFFERCELL_H
#define BUFFERCELL_H
#include <iostream>
#include "application.h"

class BufferCell
{
public:
  BufferCell() = default;
  ~BufferCell() = default;
  BufferCell(const int &index);
  bool isEmpty();
  void setApplication(Application *appPtr);
  int getIndex();
  Application *popApplicationPtr();
  Application *getApplicationPtr();
private:
  int index;
  bool empty;
  Application *appPtr;
};

#endif // BUFFERCELL_H
