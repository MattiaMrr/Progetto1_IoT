#include <Arduino.h>
#include "init.h"
#include "constants.h"
#include "leds_controller.h"
#include "game_controller.h"
#include "potentiometer_controller.h"

#include <avr/sleep.h>

extern const int BTN_PINS[];
extern const int LED_PINS[];

void setup() {
  // Inizializza bottoni, LED e display.
  initAll();

  // Inizializza il serial monitor.
  Serial.begin(9600);

  // Imposta lo stato iniziale.
  changeState(STARTUP);

  // Resetta i led.
  resetBoard();
}


void loop() {
  switch (state) {
    case STARTUP:
      int newDifficulty;
      // Pulsa il led rosso.
      pulseRedLed();

      // Read diffuculty from potentiometer.
      newDifficulty = readDifficulty();
      Serial.print("DIFFICULTY ");
      Serial.println(newDifficulty);

      //show selected difficulty with LEDs
      if (newDifficulty != difficulty) {
        difficulty = newDifficulty;
        showDifficulty(difficulty);
      }
      
      // if more than 10 seconds are elasped within this state, change state to DEEP_SLEEP. Magic number to constant?
      if (millis() - currRoundStartTime >= 10000) {
        changeState(DEEP_SLEEP);
      }

      // Check if the user pressed the button.
      // ...

      break;
    case DEEP_SLEEP:
      Serial.println("DEEP SLEEP");
      // forse devo spegnere tutte le luci non so se lo fa da solo.

      // Enable wakeup interrupts on all buttons.
      enableWakeUpInterrupts();

      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();

      /** The program will continue from here. **/
      Serial.println("WAKE UP");

      /* First thing to do is disable sleep. Then set state to STARTUP. */
      sleep_disable();

      // Disable wakeup interrupts on all button pins.
      disableWakeUpInterrupts();

      // Change state back to STARTUP.
      changeState(STARTUP);
      break;
    case PREPARE_ROUND:
      int rand_num;
      // Codice per lo stato PREPARE_ROUND
      // Scrivere GO sul display LCD.
      writeOnLCD("GO");

      // Volendo un animazione con i LED.
      //...

      delay(2000);
      if (millis() - currRoundStartTime >= 2000) {
        // Genera un numero random.
        rand_num = generateRandomNumber();

        // scrivi il numero sul display LCD.
        writeOnLCD("" + rand_num);

        // Cambia stato
        changeState(ROUND);
      }
      break;
    case ROUND:
      // Codice per lo stato ROUND.

      // Controlla input utente sui bottoni.
      readButtons();

      // Aspetta un tot di tempo, TODO: calcolare il tmepo in base alla difficoltà e al round.
      // Scaduto il tempo, controlla se l'utente ha scritto corretto. in caso cambia stato a ROUND_WIN o GAME_OVER.
      if (millis() - currRoundStartTime >= 10000) {
        changeState(checkWin(readLedStatesAsInt()) ? ROUND_WIN : GAME_OVER);
      }
      
      break;
    case ROUND_WIN:
      // Codice per lo stato ROUND_WIN
      
      // Scrivere WIN sul display LCD.
      Serial.println("WIN");
      writeOnLCD("WIN");

      // Aspetta 2 secondi.
      delay(2000);

      // Magari un animazione con i LED.
      //...

      // cambia stato a ROUND. usare una funziona apposta.
      changeState(ROUND);

      // riduce il tempo a disposizione per il round.

      break;
    case GAME_OVER:
      // Codice per lo stato GAME_OVER
      break;
  }
}
