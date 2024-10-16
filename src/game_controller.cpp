#include "game_controller.h"
#include "leds_controller.h"
#include "buttons_controller.h"
#include "constants.h"

int state;
int currRoundStartTime;
int difficulty = 1;

void changeState(int newState)
{
  state = newState;
  currRoundStartTime = millis();
}

// funzione per controllare se il round e' stato vinto
void checkWin(int userNumber, int randomNumber)
{
  if (userNumber == randomNumber)
  {
    changeState(ROUND_WIN);
  }
}

// funzione per generare un numero random.
int generateRandomNumber()
{
  randomSeed(micros());
  int random_number = rand() % 16;
  return random_number;
}

int checkButton(int userNumber)
{
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    int currentButtonState = digitalRead(buttonPins[i]);

    // transizione da HIGH a LOW e viceversa dei led
    if (currentButtonState == LOW && lastButtonState[i] == HIGH)
    {
      turnOnGreenLeds();
      digitalWrite(ledPins[i], ledState[i]);
    }

    // aggiorna ultimo stato del bottone
    lastButtonState[i] = currentButtonState;
  }

  for (int i = 0; i < 4; i++)
  {
    if (ledState[i] == HIGH)
    {
      userNumber |= (1 << i);
    }
  }
  
  delay(50);

  return userNumber;
}
