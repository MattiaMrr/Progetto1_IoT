#include <Arduino.h>
#include <EnableInterrupt.h>
#include "init.h"
#include "game_controller.h"

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

void enableStartInterrupt(){
  enableInterrupt(BTN1, b1Pressed, RISING);
}

void disableStartInterrupt(){
  disableInterrupt(BTN1);
}

void b1Pressed() {
  disableStartInterrupt();
  Serial.println("btn1 premuto");
  factor = 1 - (difficulty * 0.075);  // Goes from 0.925 at difficulty 1 to 0.7 at difficulty 4.
  changeState(PREPARE_ROUND);
  clearLCD();
}
