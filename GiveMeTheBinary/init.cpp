#include <Arduino.h>
#include "init.h"

void initButtons(const int buttonPins[], int size) {
  for (int i = 0; i < size; i++) {
    pinMode(buttonPins[i], INPUT);
  }
}

void initLeds(const int ledPins[], int size) {
  for (int i = 0; i < size; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}