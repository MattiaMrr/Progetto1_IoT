#include <Arduino.h>
#include "init.h"

void initAll(int ledPins[], int buttonPins[]) {
  buttonsInit(buttonPins);
  initLeds(ledPins);
  initDisplay();
}