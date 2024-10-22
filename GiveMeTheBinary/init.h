#ifndef INIT_H
#define INIT_H

#include "leds_controller.h"
#include "buttons_controller.h"
#include "lcd_controller.h"

void initAll();
void wakeUp();
void enableWakeUpInterrupts();
void disableWakeUpInterrupts();
void enableStartInterrupt();
void disableStartInterrupt();
void b1Pressed();
#endif // INIT_H