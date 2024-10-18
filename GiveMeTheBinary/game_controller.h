#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <Arduino.h>

extern int state;
extern unsigned long currRoundStartTime;
extern int difficulty;
extern int random_number;

void changeState(int newState);
int generateRandomNumber();
bool checkWin(int user_num);
int checkButton();
#endif // GAME_CONTROLLER_H