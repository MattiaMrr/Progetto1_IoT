#include <Arduino.h>
#include "init.h"
#include "buttons_controller.h"
#include "constants.h"
#include "leds_controller.h"
#include <avr/sleep.h>
#include "game_controller.h"
#include "potentiometer_controller.h"


int buttonPins[] = {BTN1, BTN2, BTN3, BTN4};
int ledPins[] = {L1, L2, L3, L4, LS};
int rand_num;
int user_num;

void setup() {
    Serial.begin(9600);

  // Inizializza bottoni, LED e display.
  initAll(ledPins, buttonPins);
  setupSeed();

  state = STARTUP;
}

void loop() {
  switch (state) {
    
    case STARTUP:
      // Pulsa il led rosso.
      delay(10);
      pulseRedLed();
      // Read diffuculty from potentiometer.
     // int newDifficulty = readDifficulty();

      //show selected difficulty with LEDs
      /*
      if (newDifficulty != difficulty) {
        difficulty = newDifficulty;
        showDifficulty(difficulty);
      }
      */
      if (digitalRead(BTN1) == LOW) 
      {
        changeState(PREPARE_ROUND);
      }
      
      if (millis() - currRoundStartTime >= 10000) {
        turnOffRedLed();
        changeState(DEEP_SLEEP);
      }    
      

     // state = ROUND;
      break;
      case DEEP_SLEEP:
      // Preparazione alla modalità sleep
      enableWakeUpInterrupts();
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
      sleep_enable();

     
      sleep_mode();

      sleep_disable();
      disableWakeUpInterrupts(); 
      currRoundStartTime = millis(); 
      // Dopo il risveglio, torna allo stato STARTUP
      changeState(STARTUP);
      break;
    case PREPARE_ROUND:

    writeOnLCD("Go", "");

      delay(2500);
      if (millis() - currRoundStartTime >= 2000) {
       
        rand_num = generateRandomNumber();
        writeOnLCD("Number: ", String(rand_num));
        changeState(ROUND);
      }
      break;
    case ROUND:
      // Codice per lo stato ROUND.

      // Genera un numero random.
      
      // scrivi il numero sul display LCD.
      //writeOnLCD();

      // Controlla input utente sui bottoni.
      user_num = checkButton(ledPins, rand_num);

      // dopo un certo tempo controlla se l'utente ha scritto corretto.
      if (checkWin(user_num, rand_num))
      {
        turnOffGreenLeds(ledPins);
      }
      
     
      // Aspetta un tot di tempo, TODO: calcolare il tmepo in base alla difficoltà e al round.
      
      // checkWin();
      // Scaduto il tempo, controlla se l'utente ha scritto corretto. in caso cambia stato a ROUND_WIN o GAME_OVER.
      
       if (millis() - currRoundStartTime >= 10000) {
        changeState(GAME_OVER);
      }
     
      
      break;
    case ROUND_WIN:
      // Codice per lo stato ROUND_WIN
      
     writeOnLCD("YOU WON", "");
      //writeOnLCD("WIN");

      // Aspetta 2 secondi.
      delay(2000);

      // Magari un animazione con i LED.
      //...

      // cambia stato a ROUND. usare una funziona apposta.
      changeState(PREPARE_ROUND);

      // riduce il tempo a disposizione per il round.

      break;
    case GAME_OVER:
      writeOnLCD("You lost", "");
      break;
  }
}
