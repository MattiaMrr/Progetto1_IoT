#ifndef INIT_H
#define INIT_H

#include "leds_controller.h"
#include "buttons_controller.h"
#include "lcd_manager.h"

void initAll();
void wakeUp();
void enableWakeUpInterrupts();
void disableWakeUpInterrupts();

#endif // INIT_H