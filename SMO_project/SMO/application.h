#ifndef APPLICATION_H
#define APPLICATION_H
#include "appstate_type.h"

class Application
{
public:
  Application() = default;
  ~Application() = default;
  Application(const double &tGen, const int &srcNum, const int &index);
  void addLifeTime(const double &t);
  double getGenTime() const;
  double getLifeTime() const;
  int getSrcNum() const;
  void setIndex(const int &index);
  int getIndex() const;
  void setProcessingTime(double &tProcessing);
  double getProcessingTime() const;
  double getAwaittingTime() const;
  double getReleaseTime() const;
  void setAwaittingTime(double &tEnrty);
  void setState(AppState state);
  AppState getState();
  void setBufferCellIndex(int index);
  void setDeviceIndex(int index);
  int getBufferCellIndex();
  int getDeviceIndex();
private:
  double tGen, tLife, tProcessing, tAwaitting, tRelease;
  int srcNum, index, bufferCellIndex, deviceIndex;
  AppState state;
};
#endif // APPLICATION_H
