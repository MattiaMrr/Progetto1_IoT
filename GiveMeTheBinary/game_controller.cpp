#include "game_controller.h"

int state;
int currRoundStartTime;
int difficulty;


void changeState(int newState) {
  state = newState;
  currRoundStartTime = millis();
}