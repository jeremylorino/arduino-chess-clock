#ifndef ChessPlayerTimer_h
#define ChessPlayerTimer_h

#include "Arduino.h"

class ChessPlayerTimer {
public:
  ChessPlayerTimer(unsigned long start, unsigned long elapsed, unsigned long time);
  void setTimeControl(unsigned long timeControl);
  char *getTimeString();
  void start();
  void pause();
  void reset();
  void tick();
  bool isOutOfTime();

private:
  unsigned long _start;
  unsigned long _elapsed;
  unsigned long _time;
  unsigned long _timeControl;
};

#endif

