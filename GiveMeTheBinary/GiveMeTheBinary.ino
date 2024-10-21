#include <Arduino.h>
#include "init.h"
#include "constants.h"
#include "leds_controller.h"
#include "game_controller.h"
#include "potentiometer_controller.h"

#include <avr/sleep.h>

extern const int BTN_PINS[];
extern const int LED_PINS[];

double factor;
double roundTime = ROUND_TIME;
int score = 0;

void setup() {
  // Inizializza bottoni, LED e display.
  initAll();

  setupSeed();

  // Inizializza il serial monitor.
  Serial.begin(9600);

  // Imposta lo stato iniziale.
  changeState(STARTUP);

  // Resetta i led.
  resetBoard();

  enableInterrupt(BTN1, b1Pressed, RISING);
}


void loop() {
  switch (state) {
    case STARTUP:
      int newDifficulty;
      interrupts();
      // Pulsa il led rosso.
      pulseRedLed();

      writeOnLCD("Welcome to GMB!", "Press B1 to Start");

      // Read difficulty from potentiometer.
      newDifficulty = readDifficulty();

      //show selected difficulty with LEDs
      if (newDifficulty != difficulty) {
        Serial.print("DIFFICULTY ");
        Serial.println(newDifficulty);
        difficulty = newDifficulty;
        showDifficulty(difficulty);
      }
      
      // if more than 20 seconds are elasped within this state, change state to DEEP_SLEEP. Magic number to constant?
      if (millis() - currRoundStartTime >= 20000) {
        Serial.println("20 seconds");
        changeState(DEEP_SLEEP);
        clearLCD();
      }

      break;
    case DEEP_SLEEP:
      enableWakeUpInterrupts();
      interrupts();
      resetBoard();
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();
      sleep_disable();
      disableWakeUpInterrupts();
      changeState(STARTUP);
      noInterrupts();
      break;
    case PREPARE_ROUND:
      int rand_num;
      // Codice per lo stato PREPARE_ROUND
      // Scrivere GO sul display LCD.
      writeOnLCD("GO", "");

      // Volendo un animazione con i LED.
      //...

      if (millis() - currRoundStartTime >= 2000) {
        // Genera un numero random.
        rand_num = generateRandomNumber();
        Serial.print("gen num:");
        Serial.println(rand_num);

        clearLCD();
        writeOnLCD("Number: ", String(rand_num));

        // Cambia stato
        changeState(ROUND);
      }
      break;
    case ROUND:
      // Codice per lo stato ROUND.

      // Controlla input utente sui bottoni.
      readButtons();

      // Serial.print("time in round: ");
      // Serial.println(millis() - currRoundStartTime);

      // Aspetta un tot di tempo, TODO: calcolare il tmepo in base alla difficoltà e al round.
      // Scaduto il tempo, controlla se l'utente ha scritto corretto. in caso cambia stato a ROUND_WIN o GAME_OVER.
      if (millis() - currRoundStartTime >= roundTime) {
        changeState(checkWin(readLedStatesAsInt()) ? ROUND_WIN : GAME_OVER);
      }
      
      break;
    case ROUND_WIN:
      // Incrementa il punteggio
      score++;
      
      // Scrive GOOD! e il punteggio sul display
      clearLCD();
      writeOnLCD("GOOD!", String("Score: ") + String(score));

      delay(2000);

      // Genera un nuovo numero casuale
      rand_num = generateRandomNumber();

      // Riduci il tempo disponibile per il prossimo round
      roundTime = roundTime * factor;

      // Serial.print("new roundtime: ");
      // Serial.println(roundTime);

      // Scrivi il numero sul display LCD
      clearLCD();
      writeOnLCD("Number: ", String(rand_num));

      // Cambia stato
      changeState(ROUND);
      break;
    case GAME_OVER:
      // Codice per lo stato GAME_OVER

      // Per il primo secondo luce rossa, poi tutto spento.
      if (millis() - currRoundStartTime >= 1000) {
        turnOffRedLed();
      } else {
        turnOnRedLed();
      }

      writeOnLCD("Game Over", String("Final Score: ") + String(score));

      if (millis() - currRoundStartTime >= 10000) {
        Serial.println("Restarting...");

        score = 0;
        difficulty = 0;

        // Cambia stato
        changeState(STARTUP);
      }

      break;
  }
}
