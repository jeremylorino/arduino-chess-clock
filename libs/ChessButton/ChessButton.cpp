
#include "Arduino.h"
#include "ChessButton.h"

ChessButton::ChessButton(int portNumber) {
  _portNumber = portNumber;
}

void ChessButton::setup(){
  pinMode(_portNumber, INPUT);
}

int ChessButton::getValue() {
  int port_value = 0;

  for (int i = 0; i < 10; i++)
  {
    port_value += analogRead(_portNumber);
  }
  port_value /= 10;

  return port_value;
}