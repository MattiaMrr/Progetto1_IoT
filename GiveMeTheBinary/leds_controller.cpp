#include "leds_controller.h"
#include <Arduino.h>

// Definisci gli array per i bottoni e i LED
const int LED_PINS[] = {L1, L2, L3, L4};
bool ledState[LED_COUNT];

// const int ledStates[LED_COUNT];

// Used to pulse the red led.
int fadeAmount = DEFAULT_FADE_AMOUNT;
int currIntensity = START_INTENSITY;

void initLeds() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    ledState[i] = false;
  }
}

void turnOffLed(const int ledIndex) {
  digitalWrite(LED_PINS[ledIndex], LOW);

}

void turnOnLed(const int ledIndex) {
  digitalWrite(LED_PINS[ledIndex], HIGH);
}

void turnOnGreenLeds() {
    for (int i = 1; i < LED_COUNT; i++) {
        turnOnLed(i);
    }
}

void turnOffGreenLeds() {
    for (int i = 0; i < LED_COUNT; i++) {
        turnOffLed(i);
    }
}

void turnOnRedLed() {
    digitalWrite(LS, HIGH);
}

void turnOffRedLed() {
    digitalWrite(LS, LOW);
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

void showDifficulty(int difficulty) {
    for (int i = 1; i < difficulty; i++) {
        turnOnLed(LED_PINS[i]);
    }
}

// Funzione per leggere lo stato dei LED e convertirlo in un numero intero
int readLedStatesAsInt() {
  int ledValue = 0;
  for (int i = 0; i < LED_COUNT; i++) {
    if (ledState[i]) {
      ledValue |= (1 << i);  // Imposta il bit corrispondente a 1 se il LED è acceso
    }
  }
  return ledValue;  // Restituisce il valore intero rappresentante lo stato dei LED
}
