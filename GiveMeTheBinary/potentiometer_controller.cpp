#include <Arduino.h>
#include "potentiometer_controller.h"

// Read potentiometer value and maps to value from 1 to 4.
int readDifficulty() {
  int potentiometerValue = analogRead(POT);
  Serial.print("pot val ");
  Serial.println(potentiometerValue);
  int difficulty = round(map(potentiometerValue, 0, 1023, 1, 5));  // 4 is the maximum difficulty, use constant?
  Serial.print("diff val: ");
  Serial.println(difficulty);
  return difficulty;
}

