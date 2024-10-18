#include <Arduino.h>
#include "init.h"
#include "constants.h"
#include "leds_controller.h"
#include <avr/sleep.h>
#include "game_controller.h"
#include "potentiometer_controller.h"

int buttonPins[] = {BTN1, BTN2, BTN3, BTN4};
int ledPins[] = {L1, L2, L3, L4, LS};
int rand_num = 0;
int user_num;

void setup() {
  // Inizializza bottoni, LED e display.
  initAll(ledPins, buttonPins);

  // Inizializza il serial monitor.
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BTN1), wakeUpNow, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN2), switchToRound, FALLING);

  // Resetta i led.
  resetBoard(ledPins);
}

void loop() {
  switch (state) {
    
    case STARTUP:
      // Pulsa il led rosso.
      Serial.println("startUp");
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
      
      // if more than 10 seconds are elasped within this state, change state to DEEP_SLEEP. Magic number to constant?
      
      
      if (millis() - currRoundStartTime >= 10000) {
        Serial.println("entrato nel if");
        changeState(DEEP_SLEEP);
      }    
      

     // state = ROUND;
      break;
      case DEEP_SLEEP:

      // Preparazione alla modalità sleep
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
      sleep_enable();

      resetBoard(ledPins);
      sleep_mode();

      sleep_disable();

      // Dopo il risveglio, torna allo stato STARTUP
      changeState(STARTUP);
      break;
    case PREPARE_ROUND:

    //salvo il numero generato randomicamente nella variabile rand_num
    rand_num = generateRandomNumber();
    writeOnLCD("GO");
    detachInterrupt(0);
    detachInterrupt(1);
   Serial.println(rand_num);
      // Volendo un animazione con i LED.
      //...
      delay(2500);
      if (millis() - currRoundStartTime >= 2000) {
        changeState(ROUND);
      }
      break;
    case ROUND:
      // Codice per lo stato ROUND.

      // Genera un numero random.
      
      // scrivi il numero sul display LCD.
      //writeOnLCD();

      // Controlla input utente sui bottoni.
      user_num = checkButton(user_num, ledPins, rand_num);

      // dopo un certo tempo controlla se l'utente ha scritto corretto.
      checkWin(user_num, rand_num);
     
      // Aspetta un tot di tempo, TODO: calcolare il tmepo in base alla difficoltà e al round.
      
      // checkWin();
      // Scaduto il tempo, controlla se l'utente ha scritto corretto. in caso cambia stato a ROUND_WIN o GAME_OVER.
      
       if (millis() - currRoundStartTime >= 10000) {
        changeState(GAME_OVER);
      }
     
      
      break;
    case ROUND_WIN:
      // Codice per lo stato ROUND_WIN
      
      // Scrivere WIN sul display LCD.
      Serial.println( rand_num);
      //writeOnLCD("WIN");

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
