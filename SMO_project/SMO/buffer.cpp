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
      //std::cout<<"\nApplication <" << appPtr->getSrcNum() << "." << appPtr->getIndex() << "> tries to enter buffer\n";
      //printBufferState();
      return true;
    }
  }
  //std::cout<<"\nApplication <" << appPtr->getSrcNum() << "." << appPtr->getIndex() << "> got rejected\n";
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
  //std::cout << "\nBuffer being refactored\n";
  //printBufferState();
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
          Application *appPtrToReturn = bc.getApplicationPtr();
          return appPtrToReturn;
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
  Application *appPtrToReturn = minBC->getApplicationPtr();
  return appPtrToReturn;
}
void Buffer::popThisApplicationPtr(const Application *appPtr)
{
  sourcePackage = appPtr->getSrcNum();
  for(auto &&bc : bufferList)
  {
    if(bc.getApplicationPtr()->getGenTime() == appPtr->getGenTime())
    {
      bc.popApplicationPtr();
      break;
    }
  }
  //std::cout<<"\nApplication <" << appPtr->getSrcNum() << "." << appPtr->getIndex() << "> released from buffer\n";
  //printBufferState();
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
void Buffer::updateLifeTime(double &tLifeToAdd)
{
  for(auto &&bc : bufferList)
  {
    if(!bc.isEmpty())
    {
      bc.updateApplicationLifeTime(tLifeToAdd);
    }
  }
}
