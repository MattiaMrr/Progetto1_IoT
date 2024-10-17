#include <Arduino.h>
#include <constants.h>

void buttonsInit(int buttonPins[]){
for (int i = 0; i < 4; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
}