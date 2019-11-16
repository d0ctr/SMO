#include "buffer.h"
Buffer::Buffer(const int &bufSize)
{
  for(int i = 0; i < bufSize; i++)
  {
    bufferList.push_back(BufferCell(i));
  }
  sourcePackage = -1;
  this->bufSize = bufSize;
}
bool Buffer::tryToAddApplicationPtr(Application *appPtr)
{
  for(auto&& bc : bufferList)
  {
    if(bc.isEmpty())
    {
      bc.setApplication(appPtr);
      return true;
    }
  }
  appPtr->setState(REJECTED);
  return false;
}
bool Buffer::isEmpty()
{
  for(auto &&bc : bufferList)
  {
    if(!bc.isEmpty())
    {
      return false;
    }
  }
  return true;
}
void Buffer::refactorBuffer()
{
  if(isEmpty())
  {
    return;
  }
  for(std::list<BufferCell>::iterator it1 = bufferList.begin(), it2 = ++bufferList.begin(); it2 != bufferList.end() ; ++it1, ++it2)
  {
    if(it1->isEmpty() && !it2->isEmpty())
    {
      Application *appPtrToMove = it2->popApplicationPtr();
      it1->setApplication(appPtrToMove);
    }
  }
}
Application *Buffer::getExpectedApplicationPtr()
{
  if(sourcePackage != -1)
  {
    for(auto &&bc : bufferList)
    {
      if(!bc.isEmpty())
      {
        if(bc.getApplicationPtr()->getSrcNum() == sourcePackage)
        {
          return bc.getApplicationPtr();
        }
      }
    }
    sourcePackage = -1;
  }
  BufferCell *minBC = &bufferList.front();
  for(auto &&bc : bufferList)
  {
   if(!bc.isEmpty())
   {
     if(bc.getApplicationPtr()->getSrcNum() < minBC->getApplicationPtr()->getSrcNum())
     {
       minBC = &bc;
     }
   }
  }
  return minBC->getApplicationPtr();
}
void Buffer::popThisApplicationPtr(const Application *appPtr)
{
  sourcePackage = appPtr->getSrcNum();
  for(auto &&bc : bufferList)
  {
    if(bc.getApplicationPtr() == appPtr)
    {
      bc.popApplicationPtr();
      break;
    }
  }
  refactorBuffer();
}
void Buffer::printBufferState()
{
  for(auto &&bc : bufferList)
  {
    if(!bc.isEmpty())
    {
      std::cout << "BufferCell <" << bc.getIndex() << "> has Application <" << bc.getApplicationPtr()->getSrcNum()
                << "." << bc.getApplicationPtr()->getIndex() << "> with Life time <" << bc.getApplicationPtr()->getLifeTime() << ">\n";
    }
    else
    {
      std::cout << "BufferCell <" << bc.getIndex() << "> is empty\n";
    }
  }
}
std::list<BufferCell> *Buffer::getBufferList()
{
  return &bufferList;
}
