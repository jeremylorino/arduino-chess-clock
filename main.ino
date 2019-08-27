#include <LiquidCrystal.h>
#include "libraries/constants.h"
#include <Led.h>
#include <ChessButton.h>
#include <ChessPlayerTimer.h>

unsigned long TIMECONTROLS[] = {TIME_CONTROLS};

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 0;
const byte hours = 16;

/* Change these values to set the current initial date */
const byte day = 15;
const byte month = 6;
const byte year = 15;

// define some values used by the panel and buttons
int lcd_key = 0;
int adc_key_in = 0;

int EngageTimer = 0;
int currentTimeControl = 0;

ChessPlayerTimer whiteTimer(0, 0, TIMECONTROLS[currentTimeControl]);
ChessPlayerTimer blackTimer(0, 0, TIMECONTROLS[currentTimeControl]);

int turn = TURN_NONE;

Led led(22, 24, 26);
ChessButton chessButton(A8);

int read_LCD_buttons()
{
  adc_key_in = analogRead(0);
  if (adc_key_in > 1000)
    return btnNONE;
  if (adc_key_in < 50)
    return btnRIGHT;
  if (adc_key_in < 195)
    return btnUP;
  if (adc_key_in < 380)
    return btnDOWN;
  if (adc_key_in < 555)
    return btnLEFT;
  if (adc_key_in < 790)
    return btnSELECT;
  return btnNONE;
}

void setTimeControl(unsigned long timeControl)
{
  whiteTimer.setTimeControl(timeControl);
  blackTimer.setTimeControl(timeControl);
}

void setup()
{
  Serial.begin(115200);

  chessButton.setup();
  led.setup();

  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  char juststringval[16];
  sprintf(juststringval, "%-7s %5s", "WHITE", "BLACK");
  lcd.print(juststringval);

  lcd.setCursor(8, 0);
  lcd.print('|');
}

void printWhiteTime()
{
  char *s = whiteTimer.getTimeString();
  lcd.setCursor(2, 1);
  lcd.print(s);
}

void printBlackTime()
{
  char *s = blackTimer.getTimeString();
  lcd.setCursor(9, 1);
  lcd.print(s);
}

void loop()
{
  lcd_key = read_LCD_buttons();
  int port_value = chessButton.getValue();

  if (turn == TURN_NONE)
  {
    led.setColor(0, 0, 128);
    if (port_value > 10)
    {
      lcd.setCursor(2, 0);
      char juststringval[16];
      sprintf(juststringval, "%-7s %5s", "BLACK", "WHITE");
      lcd.print(juststringval);

      lcd.setCursor(8, 0);
      lcd.print('|');
    }
    else
    {
      lcd.setCursor(2, 0);
      char juststringval[16];
      sprintf(juststringval, "%-7s %5s", "WHITE", "BLACK");
      lcd.print(juststringval);

      lcd.setCursor(8, 0);
      lcd.print('|');
    }
  }

  if (EngageTimer == 1)
  {
    if (port_value > 10 && turn != TURN_BLACK)
    {
      turn = TURN_BLACK;
      blackTimer.pause();
    }
    else if (port_value <= 10 && turn != TURN_WHITE)
    {
      turn = TURN_WHITE;
      whiteTimer.pause();
    }
  }

  switch (lcd_key)
  {
    case btnRIGHT:
    {
      if (EngageTimer == 0)
      {
        currentTimeControl++;
        if (currentTimeControl >= sizeof(TIMECONTROLS) / sizeof(unsigned long))
        {
          currentTimeControl = 0;
        }
        setTimeControl(TIMECONTROLS[currentTimeControl]);
        delay(500);
      }
      break;
    }
    case btnLEFT:
    {
      if (EngageTimer == 0)
      {
        currentTimeControl--;
        if (currentTimeControl < 0)
        {
          currentTimeControl = sizeof(TIMECONTROLS) / sizeof(unsigned long) -1;
        }
        setTimeControl(TIMECONTROLS[currentTimeControl]);
        delay(500);
      }
      break;
    }
    case btnUP:
    {
      EngageTimer = 0;

      whiteTimer.reset();
      blackTimer.reset();
      break;
    }
    case btnDOWN:
    {
      EngageTimer = 0;
      break;
    }
    case btnSELECT:
    {
      EngageTimer = 1;
      
      whiteTimer.start();
      blackTimer.start();
      
      led.setColor(0, 128, 0);
      break;
    }
  }

  if (EngageTimer == 1)
  {
    if (turn == TURN_WHITE)
    {
      if (whiteTimer.isOutOfTime()){
        led.setColor(255,0,0);
      }else {
        whiteTimer.tick();
      }
    }
    if (turn == TURN_BLACK)
    {
      if (blackTimer.isOutOfTime()){
        led.setColor(255,0,0);
      }else {
        blackTimer.tick();
      }
    }
  }

  printWhiteTime();
  printBlackTime();

}
