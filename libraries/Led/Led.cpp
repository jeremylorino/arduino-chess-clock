
#include "Arduino.h"
#include "Led.h"

Led::Led(int redPin, int greenPin, int bluePin) {
  init(redPin, greenPin, bluePin);
}

void Led::init(int redPin, int greenPin, int bluePin)
{
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
  _redValue = 0;
  _greenValue = 0;
  _blueValue = 0;
}

void Led::setup() {
  pinMode(_redPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  pinMode(_bluePin, OUTPUT);
}

void Led::setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(_redPin, red);
  analogWrite(_greenPin, green);
  analogWrite(_bluePin, blue);
}