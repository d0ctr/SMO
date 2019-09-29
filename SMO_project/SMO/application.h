#ifndef APPLICATION_H
#define APPLICATION_H
#include "appstate_type.h"

class Application
{
public:
  Application() = default;
  ~Application() = default;
  Application(const double &tGen, const int &srcNum);
  void addLifeTime(const double &t);
  double getGenTime() const;
  double getLifeTime() const;
  int getSrcNum() const;
  void setIndex(const int &index);
  int getIndex() const;
  void setProcessingTime(double &tProcessing);
  double getProcessingTime();
  double getAwaittingTime();
  void setState(AppState state);
  AppState getState();
private:
  double tGen, tLife, tProcessing;
  int srcNum;
  int index;
  AppState state;
};
#endif // APPLICATION_H
