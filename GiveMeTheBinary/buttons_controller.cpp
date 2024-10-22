#include "constants.h"
#include "leds_controller.h"
#include "buttons_controller.h"
#include <Arduino.h>

// array of the buttons pins.
const int BTN_PINS[BUTTON_COUNT] = {BTN1, BTN2, BTN3, BTN4};

void initButtons() {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(BTN_PINS[i], INPUT);
  }
}

// Reads state of all buttons and lights the corresponding LED if button state is stable.
void readButtons() {
  unsigned long currTime = millis();  // Get current time.
  static unsigned long btnTimers[BUTTON_COUNT] = {0, 0, 0, 0};  // Debounce timer for each button.
  static bool lastButtonState[BUTTON_COUNT] = {LOW, LOW, LOW, LOW}; // Last state of each button.

  for (int i = 0; i < BUTTON_COUNT; i++) {
    bool btnState = digitalRead(BTN_PINS[i]);  // Read button state.

    // If button is pressed and debounce time has passed and the button state has changed (button not held down) turn on correspoding led.
    if (btnState == HIGH  && btnState != lastButtonState[i] && currTime - btnTimers[i] >= DEBOUNCE_TIME) {
      // //Serial.print("Debounce:");
      // //Serial.println(currTime - btnTimers[i]);
      changeLedStatus(i);  // Turn on/off correspodning led.
      // Reset button timer.
      btnTimers[i] = millis();
    }
    lastButtonState[i] = btnState;  // save current button state for next fucntion call.
  }
}
