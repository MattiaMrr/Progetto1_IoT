#include <Arduino.h>

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

extern int state;
extern int currRoundStartTime;

void changeState(int newState);

#endif // GAME_CONTROLLER_H