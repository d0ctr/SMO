#ifndef APPSTATE_TYPE_H
#define APPSTATE_TYPE_H

enum AppState
{
  PREGEN = 0,
  INBUF = 1,
  INDEV = 2,
  PROCESSED = 3,
  REJECTED = -1
};
#endif // APPSTATE_TYPE_H
