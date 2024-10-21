#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <Arduino.h>

extern int state;
extern unsigned long currRoundStartTime;
extern int difficulty;
extern int random_number;
extern double factor;
extern double roundTime;
extern int score;

void changeState(int newState);
int generateRandomNumber();
bool checkWin(int user_num);
int checkButton();
void setupSeed();
#endif // GAME_CONTROLLER_H