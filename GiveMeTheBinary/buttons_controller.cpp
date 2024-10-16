#ifndef BUTTONS_CONTROLLER_H
#define BUTTONS_CONTROLLER_H
#include "constants.h"
#include <Arduino.h>

const int buttonPins[BUTTON_COUNT] = {B1, B2, B3, B4};
bool lastButtonState[4] = {HIGH, HIGH, HIGH, HIGH};


void initButtons() {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(buttonPins[i], INPUT);
  }
}

#endif // BUTTONS_CONTROLLER_H