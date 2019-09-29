#include "application.h"

Application::Application(const double &tGen, const int &srcNum)
{
  this->tGen = tGen;
  tLife = tGen;
  tProcessing = 0.;
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
  tLife += tProcessing;
  this->tProcessing = tProcessing;
}
double Application::getProcessingTime()
{
  return tProcessing;
}
double Application::getAwaittingTime()
{
  return tLife - tGen - tProcessing;
}
void Application::setState(AppState state)
{
  this->state = state;
}
AppState Application::getState()
{
  return state;
}
