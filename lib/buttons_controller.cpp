#ifndef BUTTONS_CONTROLLER_H
#define BUTTONS_CONTROLLER_H
#include "constants.h"
#include <Arduino.h>

const int buttonPins[BUTTON_COUNT] = {BTN1, BTN2, BTN3, BTN4};
bool lastButtonState[4] = {HIGH, HIGH, HIGH, HIGH};

void initButtons()
{
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    pinMode(buttonPins[i], INPUT);
  }
}

#endif // BUTTONS_CONTROLLER_H