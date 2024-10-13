#include <Arduino.h>
#include "init.h"
#include "constants.h"
#include "leds_controller.h"
#include <avr/sleep.h>

int state;
const int buttonPins[] = {B1, B2, B3, B4};
extern const int ledPins[];

void setup() {
  // Inizializza i bottoni e i LED usando le funzioni
  initButtons(buttonPins, BUTTON_COUNT);
  initLeds(ledPins, LED_COUNT);
  Serial.begin(9600);
  // Interrupt per il wakeup dallo sleep.

  state = STARTUP;
}

void loop() {
  switch (state) {
    case STARTUP:
      resetBoard();
      pulseRedLed();
      //read potentiometer to select difficulty
      //show selected difficulty with LEDs
      //after a certain time, change state to DEEP_SLEEP
      
      /* serve una variabile che salva il tempo iniziale ogni volta che cambio stato
        posso fare una funzione per cambiare stato e che salva il tempo iniziale,
        altrimenti dovrei resettare il timer a mano ogni volta che voglio cambiare stato.
      static unsigned long startTime = millis();
      if (millis() - startTime >= 10000) {
        state = DEEP_SLEEP;
      }
      */
      break;
    case DEEP_SLEEP:
      Serial.println("DEEP SLEEP");
      // forse devo spegnere tutte le luci non so se lo fa da solo.

      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();

      /** The program will continue from here. **/
      Serial.println("WAKE UP");

      /* First thing to do is disable sleep. Then set state to STARTUP. */
      sleep_disable(); 
      state = STARTUP;
      break;
    case PREPARE_ROUND:
      // Codice per lo stato PREPARE_ROUND
      // Scrivere GO sul display LCD.
      Serial.println("GO");
      // Volendo un animazione con i LED.
      delay(2000);
      break;
    case ROUND:
      // Codice per lo stato ROUND.

      // genera il numero random.


      // scrivi il numero sul display LCD.


      // dopo un certo tempo controlla se l'utente ha scritto corretto.
      delay(10000);
      //checkNumber();

      break;
    case ROUND_WIN:
      // Codice per lo stato ROUND_WIN

      // Scrivere WIN sul display LCD.
      Serial.println("WIN");

      // Aspetta 2 secondi.
      delay(2000);

      // Magari un animazione con i LED.
      //...

      // cambia stato a ROUND. usare una funziona apposta.
      state = ROUND;
      break;
    case GAME_OVER:
      // Codice per lo stato GAME_OVER
      break;
  }
}
