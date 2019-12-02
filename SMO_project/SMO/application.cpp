#include "application.h"

Application::Application(const double &tGen, const int &srcNum)
{
  this->tGen = tGen;
  tAwaitting = 0.;
  tLife = 0.;
  tProcessing = 0.;
  tRelease = 0.;
  this->srcNum = srcNum;
  state = PREGEN;
}
int Application::getSrcNum() const
{
  return srcNum;
}
double Application::getGenTime() const
{
  return tGen;
}
double Application::getLifeTime() const
{
  return tLife;
}
void Application::addLifeTime(const double &t)
{
  tLife += t;
}
void Application::setIndex(const int &index)
{
  this->index = index;
}
int Application::getIndex() const
{
  return index;
}
void Application::setProcessingTime(double &tProcessing)
{
  state = INDEV;
  tLife = tAwaitting + tProcessing;
  tRelease = tGen + tAwaitting + tProcessing;
  this->tProcessing = tProcessing;
}
void Application::setAwaittingTime(double &tEntry)
{
  if(tEntry > tGen)
  {
    tAwaitting = tEntry - tGen;
  }
  else
  {
    tAwaitting = 0.;
  }
}
double Application::getProcessingTime() const
{
  return tProcessing;
}
double Application::getAwaittingTime() const
{
  return tAwaitting;
}
void Application::setState(AppState state)
{
  this->state = state;
}
AppState Application::getState()
{
  return state;
}
double Application::getReleaseTime() const
{
  return tRelease;
}
