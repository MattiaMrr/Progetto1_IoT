#ifndef BUTTONS_CONTROLLER_H
#define BUTTONS_CONTROLLER_H
#include "constants.h"
#include "leds_controller.h"
#include <Arduino.h>

const int BTN_PINS[BUTTON_COUNT] = {BTN1, BTN2, BTN3, BTN4};
bool lastButtonState[4] = {HIGH, HIGH, HIGH, HIGH};


void initButtons() {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(BTN_PINS[i], INPUT);
  }
}

// Reads state of all buttons and lights the corresponding LED if button state is stable.
void readButtons() {
  unsigned long currTime = millis();  // Leggi il tempo corrente
  static unsigned long btnTimers[BUTTON_COUNT] = {0, 0, 0, 0};  // Timer debounce per ogni bottone

  for (int i = 0; i < BUTTON_COUNT; i++) {
    bool btnState = digitalRead(BTN_PINS[i]);  // Leggi lo stato del bottone

    // Se il bottone è premuto
    if (btnState == HIGH) {
      // Controlla se è passato abbastanza tempo dal precedente stato stabile
      if (currTime - btnTimers[i] >= DEBOUNCE_TIME) {
        turnOnLed(LED_PINS[i]);  // Accendi il LED corrispondente
        // Resetta il timer.
        btnTimers[i] = currTime;
      }
    }
  }
}

#endif // BUTTONS_CONTROLLER_H