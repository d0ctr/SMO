#include "buffer.h"
Buffer::Buffer(const int &bufSize)
{
  for(int i = 0; i < bufSize; i++)
  {
    bufferVector.push_back(BufferCell(i));
  }
  sourcePackage = -1;
  this->bufSize = bufSize;
}
double Buffer::tryToAddApplicationPtr(Application *appPtr)
{
  for(auto&& bc : bufferVector)
  {
    if(bc.isEmpty())
    {
      bc.setApplication(appPtr);
      return appPtr->getGenTime();
    }
  }
  appPtr->setState(REJECTED);
  return appPtr->getGenTime();
}
bool Buffer::isEmpty()
{
  for(auto &&bc : bufferVector)
  {
    if(!bc.isEmpty())
    {
      return false;
    }
  }
  return true;
}
bool Buffer::isFull()
{
  for(auto &&bc : bufferVector)
  {
    if(bc.isEmpty())
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
  for(std::vector<BufferCell>::iterator it1 = bufferVector.begin(), it2 = ++bufferVector.begin(); it2 != bufferVector.end() ; ++it1, ++it2)
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
    for(auto &&bc : bufferVector)
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
  BufferCell *minBC = &bufferVector.front();
  for(auto &&bc : bufferVector)
  {
   if(!bc.isEmpty() && bc.getApplicationPtr()->getSrcNum() < minBC->getApplicationPtr()->getSrcNum())
     {
       minBC = &bc;
     }
  }
  return minBC->getApplicationPtr();
}
void Buffer::popThisApplicationPtr(const Application *appPtr)
{
  sourcePackage = appPtr->getSrcNum();
  for(auto &&bc : bufferVector)
  {
    if(bc.getApplicationPtr() == appPtr)
    {
      bc.popApplicationPtr();
      break;
    }
  }
  refactorBuffer();
}
int Buffer::getSourcePackage()
{
  return sourcePackage;
}
void Buffer::printBufferState()
{
  for(auto &&bc : bufferVector)
  {
    if(!bc.isEmpty())
    {
      std::cout << "BufferCell <" << bc.getIndex() << "> has Application <" << bc.getApplicationPtr()->getSrcNum()
                << "." << bc.getApplicationPtr()->getIndex() << "> with Gen time <" << bc.getApplicationPtr()->getGenTime() << std::endl;
    }
    else
    {
      std::cout << "BufferCell <" << bc.getIndex() << "> is empty" << std::endl;
    }
  }
  std::cout << "Current package: " << getSourcePackage() << std::endl;
}
std::vector<BufferCell> *Buffer::getBufferVector()
{
  return &bufferVector;
}
