#ifndef LEDS_CONTROLLER_H
#define LEDS_CONTROLLER_H

#include "constants.h"

#define DEFAULT_FADE_AMOUNT 5
#define START_INTENSITY 0

extern const int ledPins[];
int ledState[BUTTON_COUNT];

void initLeds();
void turnOffLed(const int ledPin);
void turnOnLed(const int ledPin);
void turnOnGreenLeds();
void turnOffGreenLeds();
void turnOnRedLed();
void turnOffRedLed();
void pulseRedLed();
void resetBoard();
void showDifficulty(int difficulty);
int readLedNumer();

// getLedState(int led_pin);

#endif // LEDS_CONTROLLER_H