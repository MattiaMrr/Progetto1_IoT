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
unsigned long potentiometerValue;
float factor = 2.3;
float maxRoundTime = 0.0;
int timeConversionFactor = 10000;
float decreaseTimeFactor = 200.0;
int score = 0;
int lowestTime = 3000;

void setup()
{
  Serial.begin(9600);
  initAll(ledPins, buttonPins);
  setupSeed();
  state = STARTUP;
}

void loop()
{
  switch (state)
  {

  case STARTUP:
    if (millis() - currRoundStartTime >= 100)
    {
      pulseRedLed();
    }
    writeOnLCD("Welcome to GMB! ", String("Press B1 to Start"));

    potentiometerValue = readDifficulty();
    showDifficulty(potentiometerValue, ledPins);

    if (digitalRead(BTN1) == LOW)
    {
      turnOffRedLed();
      maxRoundTime = (factor / potentiometerValue) * timeConversionFactor;
      clearLCD();
      changeState(PREPARE_ROUND);
    }

    if (millis() - currRoundStartTime >= 10000)
    {
      turnOffRedLed();
      turnOffGreenLeds(ledPins);
      changeState(DEEP_SLEEP);
    }

    break;

  case DEEP_SLEEP:
    /*Preparazione alla modalità sleep*/
    enableWakeUpInterrupts();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    disableWakeUpInterrupts();
    currRoundStartTime = millis();
    changeState(STARTUP);
    break;

  case PREPARE_ROUND:
    writeOnLCD("GO", "");
    turnOffGreenLeds(ledPins);
    if (millis() - currRoundStartTime >= 2000)
    {
      rand_num = generateRandomNumber();
      writeOnLCD("Number: ", String(rand_num));
      changeState(ROUND);
    }
    break;

  case ROUND:
    user_num = checkButton(ledPins, rand_num);
    /*Scaduto il tempo, controlla se l'utente ha scritto corretto. Quindi cambia stato a ROUND_WIN o GAME_OVER.*/
    if (millis() - currRoundStartTime >= maxRoundTime)
    {
      if (checkWin(user_num, rand_num))
      {
        resetButtonsAndLeds(buttonPins, ledPins);
        turnOffGreenLeds(ledPins);
        clearLCD();
      }
      else
      {
        turnOnRedLed();
        delay(1000);
        turnOffRedLed();
        turnOffGreenLeds(ledPins);
        resetButtonsAndLeds(buttonPins, ledPins);
        changeState(GAME_OVER);
      }
    }
    break;

  case ROUND_WIN:
    /*Codice per lo stato ROUND_WIN*/
    score++;
    writeOnLCD("GOOD!", String("Score: ") + String(score));
    delay(2000);
    changeState(PREPARE_ROUND);
    clearLCD();
    if (maxRoundTime >= lowestTime)
    {
      maxRoundTime = maxRoundTime - decreaseTimeFactor;
    }
    break;

  case GAME_OVER:

    writeOnLCD("GAME OVER ", String("Final Score: ") + String(score));
    if (millis() - currRoundStartTime >= 10000)
    {
      changeState(STARTUP);
      score = 0;
    }

    break;
  }
}
