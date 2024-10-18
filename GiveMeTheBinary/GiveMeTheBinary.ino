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
      interrupts();
      // Pulsa il led rosso.
      pulseRedLed();

      // Read difficulty from potentiometer.
      newDifficulty = readDifficulty();
      Serial.print("DIFFICULTY ");
      Serial.println(newDifficulty);

      //show selected difficulty with LEDs
      if (newDifficulty != difficulty) {
        difficulty = newDifficulty;
        showDifficulty(difficulty);
      }
      
      // Check if the user pressed the button.
      if(readButton(0)) {
        Serial.println("PORCOD");
        factor = 1 - (difficulty * 0.075);  // Goes from 0.925 at difficulty 1 to 0.7 at difficulty 4.
        changeState(PREPARE_ROUND);
      }
      
      // if more than 10 seconds are elasped within this state, change state to DEEP_SLEEP. Magic number to constant?
      if (millis() - currRoundStartTime >= 10000) {
        Serial.println("10 seconds");
        changeState(DEEP_SLEEP);
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

        char buffer[10]; 
        itoa(rand_num, buffer, 10); // Converte rand_num in stringa in base 10
        // scrivi il numero sul display LCD.
        writeOnLCD(buffer, "");

        // Cambia stato
        changeState(ROUND);
      }
      break;
    case ROUND:
      // Codice per lo stato ROUND.

      // Controlla input utente sui bottoni.
      readButtons();

      Serial.print("time in round: ");
      Serial.println(millis() - currRoundStartTime);

      // Aspetta un tot di tempo, TODO: calcolare il tmepo in base alla difficoltà e al round.
      // Scaduto il tempo, controlla se l'utente ha scritto corretto. in caso cambia stato a ROUND_WIN o GAME_OVER.
      if (millis() - currRoundStartTime >= roundTime) {
        changeState(checkWin(readLedStatesAsInt()) ? ROUND_WIN : GAME_OVER);
      }
      
      break;
    case ROUND_WIN:
      // Incrementa il punteggio
      score++;
      
      // Converte il punteggio in stringa
      char buffer[10]; 
      itoa(score, buffer, 10); // Converte score in stringa in base 10
      
      // Combina la stringa "Score: " con il punteggio
      char message[20]; // Assicurati che il buffer sia abbastanza grande
      sprintf(message, "Score: %s", buffer); // Combina la stringa "Score: " con il contenuto di buffer

      // Scrive GOOD! e il punteggio sul display
      writeOnLCD("GOOD!", message);

      delay(2000);

      // Genera un nuovo numero casuale
      rand_num = generateRandomNumber();

      // Riduci il tempo disponibile per il prossimo round
      roundTime = roundTime * factor;
      Serial.print("new roundtime: ");
      Serial.println(roundTime);

      // Converte il numero casuale in stringa
      itoa(rand_num, buffer, 10); // Converte rand_num in stringa in base 10
      
      // Scrivi il numero sul display LCD
      writeOnLCD("Number: ", buffer);

      // Cambia stato
      changeState(ROUND);
      break;
    case GAME_OVER:
      // Codice per lo stato GAME_OVER

      //luce rossa per un secondo
      //...
      break;
  }
}
