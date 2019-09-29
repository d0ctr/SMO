#include "buffercell.h"
BufferCell::BufferCell(const int &index)
{
  this->index = index;
  empty = true;
  appPtr = nullptr;
}
bool BufferCell::isEmpty()
{
  return empty;
}
void BufferCell::setApplication(Application *appPtr)
{
  empty = false;
  this->appPtr = appPtr;
  appPtr->setState(INBUF);
}
int BufferCell::getIndex()
{
  return index;
}
Application *BufferCell::popApplicationPtr()
{
  Application *appPtrToReturn = appPtr;
  appPtr = nullptr;
  empty = true;
  return appPtrToReturn;
}
Application *BufferCell::getApplicationPtr()
{
  return appPtr;
}
void BufferCell::updateApplicationLifeTime(double &tLifeToAdd)
{
  appPtr->addLifeTime(tLifeToAdd);
}
