#include "leds_controller.h"
#include <Arduino.h>

// Definisci gli array per i bottoni e i LED
const int ledPins[] = {LS, L1, L2, L3, L4};
// const int ledStates[LED_COUNT];

// Used to pulse the red led.
int fadeAmount = DEFAULT_FADE_AMOUNT;
int currIntensity = START_INTENSITY;

void turnOffLed(const int ledPin) {
  digitalWrite(ledPin, LOW);
}

void turnOnLed(const int ledPin) {
  digitalWrite(ledPin, HIGH);
}

void turnOnGreenLeds() {
    for (int i = 1; i < LED_COUNT; i++) {
        turnOnLed(ledPins[i]);
    }
}

void turnOffGreenLeds() {
    for (int i = 0; i < LED_COUNT; ++i) {
        turnOnLed(ledPins[i]);
    }
}

void turnOnRedLed() {
    turnOnLed(LS);
}

void turnOffRedLed() {
    turnOnLed(LS);
}

void pulseRedLed() {
    analogWrite(LS, currIntensity);
    currIntensity += fadeAmount;
    if (currIntensity == 0 || currIntensity == 255) {
        fadeAmount = -fadeAmount;
    }
}

void resetBoard(){
    turnOffGreenLeds();
    turnOffRedLed();
}