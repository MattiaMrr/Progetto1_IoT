#include <Arduino.h>

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

extern int state;
extern int currRoundStartTime;
extern int difficulty;
extern int random_number;

void changeState(int newState);
int generateRandomNumber();
bool checkWin(int user_num, int rand_num);
int checkButton(int user_num, int ledPins[], int randomNumber);
#endif // GAME_CONTROLLER_H