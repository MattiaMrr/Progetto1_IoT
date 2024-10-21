#ifndef LEDS_CONTROLLER_H
#define LEDS_CONTROLLER_H

#include "constants.h"

#define DEFAULT_FADE_AMOUNT 15
#define START_INTENSITY 0
#define MAX_INTENSITY 255 

extern const int LED_PINS[LED_COUNT];
extern bool ledState[LED_COUNT];

void initLeds();
void turnOffLed(const int ledPin);
void turnOnLed(const int ledPin);
void changeLedStatus(const int ledIndex);
void turnOnGreenLeds();
void turnOffGreenLeds();
void turnOnRedLed();
void turnOffRedLed();
void pulseRedLed();
void resetBoard();
void showDifficulty(int difficulty);
int readLedNumer();
int readLedStatesAsInt();

// getLedState(int led_pin);

#endif // LEDS_CONTROLLER_H