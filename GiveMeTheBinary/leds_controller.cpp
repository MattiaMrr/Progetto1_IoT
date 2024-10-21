#include "leds_controller.h"
#include <Arduino.h>

// Definisci gli array per i bottoni e i LED
const int LED_PINS[LED_COUNT] = {L1, L2, L3, L4};
bool ledState[LED_COUNT];

// const int ledStates[LED_COUNT];

// Used to pulse the red led.
int fadeAmount = DEFAULT_FADE_AMOUNT;
int currIntensity = START_INTENSITY;
unsigned long previousMillis = 0; // Memorizza l'ultimo tempo di aggiornamento

void initLeds() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    ledState[i] = false;
  }
}

void turnOffLed(const int ledIndex) {
  digitalWrite(LED_PINS[ledIndex], LOW);
  ledState[ledIndex] = false;
  Serial.print("OFF PIN ");
  Serial.print(LED_PINS[ledIndex]);
  Serial.print(" INDEX ");
  Serial.println(ledIndex);
}

void turnOnLed(const int ledIndex) {
  digitalWrite(LED_PINS[ledIndex], HIGH);
  ledState[ledIndex] = true;
  Serial.print("ON PIN ");
  Serial.print(LED_PINS[ledIndex]);
  Serial.print(" INDEX ");
  Serial.println(ledIndex);
}

void changeLedStatus(const int ledIndex) {
  if (ledState[ledIndex] == HIGH) {
    turnOffLed(ledIndex);  // Se il LED è già acceso, lo spegne
  } else {
    turnOnLed(ledIndex);   // Se il LED è spento, lo accende
  }
}

void turnOnGreenLeds() {
    for (int i = 0; i < LED_COUNT; i++) {
        turnOnLed(i);
    }
}

void turnOffGreenLeds() {
    for (int i = 0; i < LED_COUNT; i++) {
        turnOffLed(i);
    }
}

void turnOnRedLed() {
    digitalWrite(LS, HIGH);
    Serial.println("RED ON");
}

void turnOffRedLed() {
    digitalWrite(LS, LOW);
    Serial.println("RED OFF");
}

void pulseRedLed() {
  unsigned long currentMillis = millis(); // Ottieni il tempo attuale

    // Controlla se è trascorso l'intervallo di tempo
    if (currentMillis - previousMillis >= 20) {
      previousMillis = currentMillis; // Salva il tempo attuale
      Serial.print("RED INT ");
      Serial.println(currIntensity);
      currIntensity += fadeAmount;
      if (currIntensity <= 0 || currIntensity >= MAX_INTENSITY) {
          fadeAmount = -fadeAmount;
      } else {
        analogWrite(LS, currIntensity);
      }
    }
}
void resetBoard(){
    turnOffGreenLeds();
    turnOffRedLed();
}

void showDifficulty(int difficulty) {
    for (int i = 0; i < LED_COUNT; i++) {
      if (i < difficulty)
        turnOnLed(i);
      else
        turnOffLed(i);
    }
}

// Funzione per leggere lo stato dei LED e convertirlo in un numero intero
int readLedStatesAsInt() {
  int ledValue = 0;
  for (int i = 0; i < LED_COUNT; i++) { // Ciclo normale
    if (ledState[LED_COUNT - 1 - i]) { // Leggi dallo stato dei LED partendo dall'ultimo
      ledValue |= (1 << i); // Imposta il bit corrispondente a 1 se il LED è acceso
    }
  }
  Serial.print("NUM: ");
  Serial.println(ledValue);
  return ledValue; // Restituisce il valore intero rappresentante lo stato dei LED
}