#include "HardwareSerial.h"
#include "game_controller.h"
#include "leds_controller.h"
#include "buttons_controller.h"
#include "constants.h"

int state;
unsigned long currRoundStartTime;
int difficulty = 0;
int F = 1;
int randomNum;

void changeState(int newState)
{
  Serial.print("Stato: ");
  Serial.println(newState);
  resetBoard();
  state = newState;
  currRoundStartTime = millis();
}

// funzione per controllare se il round e' stato vinto
bool checkWin(int guess)
{
  return guess == randomNum;
}

// funzione per generare un numero random.
int generateRandomNumber()
{
  randomSeed(micros());
  randomNum = rand() % 16;
  return randomNum;
}
