#ifndef LEDS_CONTROLLER_H
#define LEDS_CONTROLLER_H

#include "constants.h"

#define DEFAULT_FADE_AMOUNT 5
#define START_INTENSITY 0


void initLeds(int ledPins[]);
void turnOffLed(int ledPin);
void turnOnLed(int ledPin);
void turnOnGreenLeds(int ledPins[]);
void turnOffGreenLeds(int ledPins[]);
void turnOnRedLed();
void turnOffRedLed();
void pulseRedLed();
void resetBoard(int ledPins[]);
void showDifficulty(int difficulty, int ledPins[]);

// getLedState(int led_pin);

#endif // LEDS_CONTROLLER_H