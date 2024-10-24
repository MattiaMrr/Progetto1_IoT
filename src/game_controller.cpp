#include "game_controller.h"
#include "leds_controller.h"
#include "buttons_controller.h"
#include "constants.h"
#include "EnableInterrupt.h"

int state;
unsigned long currRoundStartTime;
unsigned long difficulty = 0;
int ledState[BUTTON_COUNT];
int lastButtonState[BUTTON_COUNT];
extern int buttonPins[BUTTON_COUNT];

void changeState(int newState)
{
  state = newState;
  currRoundStartTime = millis();
}

bool checkWin(int userNumber, int randomNumber)
{
  if (userNumber == randomNumber)
  {
    changeState(ROUND_WIN);
    return true;
  }
  return false;
}

int generateRandomNumber()
{
  int random_number = random() % 16;
  return random_number;
}

int checkButton(int ledPins[], int randomNumber)
{
  // Array per tracciare lo stato dei pulsanti e dei LED
  int userNumber = 0;
  for (int i = 0; i < 4; i++)
  {
    int currentButtonState = digitalRead(buttonPins[i]);

    if (currentButtonState == LOW && lastButtonState[i] == HIGH)
    {
      ledState[i] = !ledState[i];
      digitalWrite(ledPins[i], ledState[i]);
    }
    lastButtonState[i] = currentButtonState;
  }

  for (int i = 0; i < 4; i++)
  {
    if (ledState[i] == HIGH)
    {
      userNumber |= (1 << (3 - i));
    }
  }

  delay(50); // Piccola pausa per evitare debounce

  return userNumber;
}

void resetButtonsAndLeds(int buttonPins[], int ledPins[])
{
  for (int i = 0; i < 4; i++)
  {
    lastButtonState[i] = HIGH;
    ledState[i] = LOW;
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void setupSeed()
{
  randomSeed(analogRead(A1));
}

void wakeUpNow()
{
  changeState(STARTUP);
}

void switchToRound()
{
  changeState(PREPARE_ROUND);
}

void enableWakeUpInterrupts()
{
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    enableInterrupt(buttonPins[i], wakeUpNow, RISING);
  }
}

void disableWakeUpInterrupts()
{
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    disableInterrupt(buttonPins[i]);
  }
}
