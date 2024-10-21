#include <Arduino.h>

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

extern int state;
extern unsigned long int currRoundStartTime;
extern unsigned long difficulty;
extern int random_number;

void changeState(int newState);
int generateRandomNumber();
bool checkWin(int user_num, int rand_num);
int checkButton(int ledPins[], int randomNumber);
void wakeUpNow();
void switchToRound();
void enableWakeUpInterrupts();
void disableWakeUpInterrupts(); 
void resetButtonsAndLeds(int buttonPins[], int ledPins[]);
void setupSeed();
#endif // GAME_CONTROLLER_H