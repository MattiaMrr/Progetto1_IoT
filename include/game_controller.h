#include <Arduino.h>

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

extern int state;
extern int currRoundStartTime;
extern int difficulty;
extern int random_number;

void changeState(int newState);
int generateRandomNumber();
bool checkWin();

#endif // GAME_CONTROLLER_H