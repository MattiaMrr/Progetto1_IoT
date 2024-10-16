#include <Arduino.h>

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

extern int state;
extern int currRoundStartTime;
extern int difficulty;
extern int random_number;

void changeState(int newState);
int generateRandomNumber();
void checkWin(int user_num, int rand_num);
int checkButton();
#endif // GAME_CONTROLLER_H