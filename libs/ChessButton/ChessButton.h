#ifndef ChessButton_h
#define ChessButton_h

#include "Arduino.h"

class ChessButton {
public:
  ChessButton(int portNumber);
  void setup();
  int getValue();

private:
  int _portNumber;
};

#endif

