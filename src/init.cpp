#include <Arduino.h>
#include "init.h"

void initAll() {
  initButtons();
  initLeds();
  initDisplay();
}