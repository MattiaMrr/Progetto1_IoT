#include <Arduino.h>
#include "potentiometer_controller.h"

int readDifficulty() {
    int potentiometerValue = analogRead(POT);
    int difficulty = map(potentiometerValue, 0, 1023, 1, 4);  // 4 is the maximum difficulty, use constant?
    return difficulty;
}

