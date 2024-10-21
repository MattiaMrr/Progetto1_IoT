#include "leds_controller.h"
#include <Arduino.h>

// Array with the led pins, maybe should be in constants file.
const int LED_PINS[LED_COUNT] = {L1, L2, L3, L4};
// Array that saves the current led state.
bool ledState[LED_COUNT];

// Used to pulse the red led.
int fadeAmount = DEFAULT_FADE_AMOUNT;
int currIntensity = START_INTENSITY;

// Initialize all leds, pinmode output.
void initLeds() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    ledState[i] = false;
  }
}

// Turn off the led of the specified index.
void turnOffLed(const int ledIndex) {
  digitalWrite(LED_PINS[ledIndex], LOW);  // actual turn off.
  ledState[ledIndex] = false;             // memorize the change.

  Serial.print("turn off pin: ");
  Serial.print(LED_PINS[ledIndex]);
  Serial.print(" on index: ");
  Serial.println(ledIndex);
}

// Turn on the led of the specified index.
void turnOnLed(const int ledIndex) {
  digitalWrite(LED_PINS[ledIndex], HIGH);
  ledState[ledIndex] = true;
  
  Serial.print("turn off pin: ");
  Serial.print(LED_PINS[ledIndex]);
  Serial.print(" on index: ");
  Serial.println(ledIndex);
}

// if led is on -> turn off, if off -> turn on.
void changeLedStatus(const int ledIndex) {
  if (ledState[ledIndex] == HIGH) {
    turnOffLed(ledIndex);
  } else {
    turnOnLed(ledIndex);
  }
}

// turn on all green leds.
void turnOnGreenLeds() {
    for (int i = 0; i < LED_COUNT; i++) {
        turnOnLed(i);
    }
}

// turn off all green leds.
void turnOffGreenLeds() {
    for (int i = 0; i < LED_COUNT; i++) {
        turnOffLed(i);
    }
}

// turn on red led
void turnOnRedLed() {
    digitalWrite(LS, HIGH);
    Serial.println("RED ON");
}

// turn off red led
void turnOffRedLed() {
    digitalWrite(LS, LOW);
    Serial.println("RED OFF");
}

// Pulse the red led, updated every 20 milliseconds.
void pulseRedLed() {
  unsigned long currentMillis = millis(); // Get current time
  static unsigned long previousMillis = 0; // Save last time.

  // Check if 20 millis have elapsed. If so use analogwrite to turn on the led with a certain intensity.
  if (currentMillis - previousMillis >= 20) {
    previousMillis = currentMillis;

    Serial.print("Red led intensity: ");
    Serial.println(currIntensity);

    // Increase or decrease intesity.
    currIntensity += fadeAmount;
    // Change sign of fadeamount if over the boundaries.
    if (currIntensity <= MIN_INTENSITY || currIntensity >= MAX_INTENSITY) {
        fadeAmount = -fadeAmount;
    } else {
      analogWrite(LS, currIntensity);
    }
  }
}

// Turn all leds off.
void resetBoard(){
    turnOffGreenLeds();
    turnOffRedLed();
}

// Take a value from 1 to 4 and show it on the leds.
void showDifficulty(int difficulty) {
  // go though all leds, and turn on the first n = difficulty and off the remaining ones.
  for (int i = 0; i < LED_COUNT; i++) {
    if (i < difficulty)
      turnOnLed(i);
    else
      turnOffLed(i);
  }
}

// Read the leds statuses and converts it into an integer value.
int readLedStatesAsInt() {
  int ledValue = 0;
  for (int i = 0; i < LED_COUNT; i++) {
    // Read from last led to first led, little endian.
    if (ledState[LED_COUNT - 1 - i]) {
      ledValue |= (1 << i); // If led is on corresponding bit is set to 1.
    }
  }
  Serial.print("Number inserted: ");
  Serial.println(ledValue);
  return ledValue; // Return the integer value read.
}