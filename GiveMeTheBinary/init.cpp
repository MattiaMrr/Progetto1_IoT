#include <Arduino.h>
#include <EnableInterrupt.h>
#include "init.h"
#include "game_controller.h"

// Initialize buttons leds and lcd.
void initAll() {
  initButtons();
  initLeds();
  initDisplay();
}


// Function that is called to manage the interrupts during the deep sleep state, actually empty.
void wakeUp() {

}

// Enable the interrupts for the wakeup on ALL the buttons.
void enableWakeUpInterrupts() {
  for(int i = 0; i < BUTTON_COUNT; i++) {
    enableInterrupt(BTN_PINS[i], wakeUp, CHANGE);
  }
}

// Disable the interrupts for the wakeup on ALL the buttons.
void disableWakeUpInterrupts() {
  for(int i = 0; i < BUTTON_COUNT; i++) {
    disableInterrupt(BTN_PINS[i]);
  }
}

// Enable the interrupt to switch from STARTUP to PREPARE_ROUND.
void enableStartInterrupt(){
  enableInterrupt(BTN1, b1Pressed, RISING);
}

// Disable the interrupts for the wakeup on ALL the buttons.
void disableStartInterrupt(){
  disableInterrupt(BTN1);
}

// Function called by interrupt, change state to PREPARE_ROUND.
void b1Pressed() {
  disableStartInterrupt();
  //Serial.println("btn1 premuto");
  changeState(PREPARE_ROUND);
}
