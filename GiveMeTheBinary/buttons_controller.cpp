#include "constants.h"
#include "leds_controller.h"
#include "buttons_controller.h"
#include <Arduino.h>

const int BTN_PINS[BUTTON_COUNT] = {BTN1, BTN2, BTN3, BTN4};

void initButtons() {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(BTN_PINS[i], INPUT);
  }
}

// Reads state of all buttons and lights the corresponding LED if button state is stable.
void readButtons() {
  unsigned long currTime = millis();  // Leggi il tempo corrente
  static unsigned long btnTimers[BUTTON_COUNT] = {0, 0, 0, 0};  // Timer debounce per ogni bottone
  static bool lastButtonState[BUTTON_COUNT] = {LOW, LOW, LOW, LOW};

  for (int i = 0; i < BUTTON_COUNT; i++) {
    bool btnState = digitalRead(BTN_PINS[i]);  // Leggi lo stato del bottone

    // Se il bottone è premuto
    if (btnState == HIGH  && btnState != lastButtonState[i] && currTime - btnTimers[i] >= DEBOUNCE_TIME) {
      Serial.print("Debounce:");
      Serial.println(currTime - btnTimers[i]);
      changeLedStatus(i);  // Accendi o spegni il LED corrispondente
      // Resetta il timer.
      btnTimers[i] = millis();
    }
    lastButtonState[i] = btnState;
  }
}
