
#include "Arduino.h"
#include "ChessPlayerTimer.h"

int getMinutes(unsigned long elapsed) {
  float h, m, s, ms;
  unsigned long over;
  h = int(elapsed / 3600000);
  over = elapsed % 3600000;
  m = int(over / 60000);
  return m;
}
int getSeconds(unsigned long elapsed) {
  float h, m, s, ms;
  unsigned long over;
  h = int(elapsed / 3600000);
  over = elapsed % 3600000;
  m = int(over / 60000);
  over = over % 60000;
  s = int(over / 1000);
  return s;
}

void timeToString(char *buff, unsigned long start, unsigned long elapsed)
{
  float h, m, s, ms;
  unsigned long over;
  String res = "";
  h = int(elapsed / 3600000);
  over = elapsed % 3600000;
  m = int(over / 60000);
  over = over % 60000;
  s = int(over / 1000);
  ms = over % 1000;

  dtostrf(m, 1, 0, buff);
  if (m > 9)
  {
    res += buff;
  }
  else
  {
    res += "0";
    res += buff;
  }

  res += ":";

  dtostrf(s, 1, 0, buff);
  if (s > 9)
  {
    res += buff;
  }
  else
  {
    res += "0";
    res += buff;
  }

  res.toCharArray(buff, 7);
}

ChessPlayerTimer::ChessPlayerTimer(unsigned long start, unsigned long elapsed, unsigned long time) {
  _start = start;
  _elapsed = elapsed;
  _time = time;
}

void ChessPlayerTimer::setTimeControl(unsigned long timeControl) {
  _time = timeControl;
  _timeControl = timeControl;
}

char *ChessPlayerTimer::getTimeString() {
  char *buff = "00:00  ";
  timeToString(buff, _start, _time - _elapsed);
  sprintf(buff, "%-7s", buff);
  return buff;
}

void ChessPlayerTimer::start() {
  _elapsed = 0;
  _start = millis();
}

void ChessPlayerTimer::pause() {
  _time -= _elapsed;
  _elapsed = 0;
  _start = millis();
}

void ChessPlayerTimer::reset() {
  _elapsed = 0;
  _time = _timeControl;
}

void ChessPlayerTimer::tick() {
  _elapsed = millis() - _start;
}

bool ChessPlayerTimer::isOutOfTime() {
  int m = getMinutes(_time - _elapsed);
  int s = getSeconds(_time - _elapsed);
  if ((m <= 0 && s <= 0) || _time <= 0){
    return true;
  }

  return false;
}
