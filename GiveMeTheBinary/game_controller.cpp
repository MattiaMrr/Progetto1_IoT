#include "Arduino.h"
#include "HardwareSerial.h"
#include "game_controller.h"
#include "leds_controller.h"
#include "buttons_controller.h"
#include "constants.h"
#include "lcd_manager.h"

int state;  // The current state.
unsigned long currRoundStartTime;   // The time spent in the current state.
int difficulty = 0;
int randomNum;  // Number to be translated.

double factor;  // factor used to decrease time each round.
double roundTime = ROUND_TIME; // time available each round.
int score = 0;

// Change the game state, resetting the board and the state timer.
// No interrupts during the change of game state.
void changeState(const int newState)
{
  noInterrupts();
  resetBoard();
  state = newState;
  currRoundStartTime = millis();
  interrupts();
}

// Check if the guess is correct.
bool checkWin(int guess)
{
  return guess == randomNum;
}

// Generate the random number from 0 to 15.
int generateRandomNumber()
{
  randomNum = random() % 16;
  return randomNum;
}

// Generates a random seed for random based on a read on an unused analogic pin. 
void setupSeed(){
  randomSeed(analogRead(A1));
}

// Sets the game difficulty.
void setDifficulty(const int diff) {
  difficulty = diff;
  factor = 1 - (difficulty * 0.075);  // Goes from 0.925 at difficulty 1 to 0.7 at difficulty 4.
}

void updateRoundTime() {
  roundTime = roundTime * factor;
}

