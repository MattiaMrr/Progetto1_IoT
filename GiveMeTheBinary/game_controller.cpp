#include "game_controller.h"
#include "leds_controller.h"
#include "buttons_controller.h"
#include "constants.h"

int state;
int currRoundStartTime;
int difficulty = 1;
int randomNum;

void changeState(int newState)
{
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

int checkButton()
{
  // for (int i = 0; i < BUTTON_COUNT; i++)
  // {
  //   int currentButtonState = digitalRead(BTN_PINS[i]);

  //   // transizione da HIGH a LOW e viceversa dei led
  //   if (currentButtonState == LOW && lastButtonState[i] == HIGH)
  //   {
  //     turnOnGreenLeds();
  //     digitalWrite(LED_PINS[i], ledState[i]);
  //   }

  //   // aggiorna ultimo stato del bottone
  //   lastButtonState[i] = currentButtonState;
  // }

  // for (int i = 0; i < 4; i++)
  // {
  //   if (ledState[i] == HIGH)
  //   {
  //     userNumber |= (1 << i);
  //   }
  // }
  
  // delay(50);

  // return userNumber;
  return 0;
}
