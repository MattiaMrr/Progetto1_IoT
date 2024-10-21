#include <Arduino.h>
#include "init.h"
#include "buttons_controller.h"
#include "constants.h"
#include "leds_controller.h"
#include <avr/sleep.h>
#include "game_controller.h"
#include "potentiometer_controller.h"

int buttonPins[] = {BTN4, BTN3, BTN2, BTN1};
int ledPins[] = {L4, L3, L2, L1, LS};
int rand_num;
int user_num;
unsigned long potentiometerValue;
float factor = 2.3;
float maxRoundTime = 0.0;
int timeConversionFactor = 10000;
float decreaseTimeFactor = 150.0;
int score = 0;
int lowestTime = 3;

void setup()
{
  Serial.begin(9600);

  // Inizializza bottoni, LED e display.
  initAll(ledPins, buttonPins);
  setupSeed();

  state = STARTUP;
}

void loop()
{
  switch (state)
  {

  case STARTUP:
    // Pulsa il led rosso.
    delay(10);
    pulseRedLed();
    // Read diffuculty from potentiometer.
    potentiometerValue = readDifficulty();
    Serial.println(potentiometerValue);
    // show selected difficulty with LEDs

    showDifficulty(potentiometerValue, ledPins);

    if (digitalRead(BTN1) == LOW)
    {
      turnOffRedLed();
      maxRoundTime = (factor / potentiometerValue) * timeConversionFactor;
      changeState(PREPARE_ROUND);
    }

    if (millis() - currRoundStartTime >= 10000)
    {
      turnOffRedLed();
      turnOffGreenLeds(ledPins);
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
    turnOffGreenLeds(ledPins);

    delay(2500);
    if (millis() - currRoundStartTime >= 2000)
    {
      rand_num = generateRandomNumber();
      writeOnLCD("Number: ", String(rand_num));
      changeState(ROUND);
    }
    break;
  case ROUND:

    // Controlla input utente sui bottoni.
    user_num = checkButton(ledPins, rand_num);
    Serial.println(maxRoundTime);

    // Scaduto il tempo, controlla se l'utente ha scritto corretto. in caso cambia stato a ROUND_WIN o GAME_OVER.
    if (millis() - currRoundStartTime >= maxRoundTime)
    {
      if (checkWin(user_num, rand_num))
      {
        resetButtonsAndLeds(buttonPins, ledPins);
        turnOffGreenLeds(ledPins);
      }
      else
        changeState(GAME_OVER);
    }

    break;
  case ROUND_WIN:
    // Codice per lo stato ROUND_WIN
    score++;
    writeOnLCD("YOU WON", String("Score: ") + String(score));
    delay(2000);
    changeState(PREPARE_ROUND);
    clearLCD();
    if (maxRoundTime >= lowestTime)
    {
    maxRoundTime = maxRoundTime - decreaseTimeFactor;
    }

    break;
  case GAME_OVER:
    writeOnLCD("You lost", String("Final score: " + String(score)));
    break;
  }
}
