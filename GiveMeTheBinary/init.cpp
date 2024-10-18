#include <Arduino.h>
#include <EnableInterrupt.h>
#include "init.h"

void initAll() {
  initButtons();
  initLeds();
  initDisplay();
}

void wakeUp() {

}

void enableWakeUpInterrupts() {
  for(int i = 0; i < BUTTON_COUNT; i++) {
    enableInterrupt(BTN_PINS[i], wakeUp, CHANGE);
  }
}

void disableWakeUpInterrupts() {
  for(int i = 0; i < BUTTON_COUNT; i++) {
    disableInterrupt(BTN_PINS[i]);
  }
}

