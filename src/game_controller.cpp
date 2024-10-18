#include "game_controller.h"
#include "leds_controller.h"
#include "buttons_controller.h"
#include "constants.h"
#include "EnableInterrupt.h"

int state;
int currRoundStartTime;
int difficulty = 1;
int ledState[BUTTON_COUNT];
int lastButtonState[BUTTON_COUNT];
extern int buttonPins[BUTTON_COUNT];

void changeState(int newState)
{
  state = newState;
  currRoundStartTime = millis();
}

// funzione per controllare se il round e' stato vinto
bool checkWin(int userNumber, int randomNumber)
{
  if (userNumber == randomNumber)
  {
    changeState(ROUND_WIN);
    return true;
  }
  return false;
}

// funzione per generare un numero random.
int generateRandomNumber()
{
  randomSeed(micros());
  int random_number = rand() % 16;
  return random_number;
}

int checkButton(int userNumber, int ledPins[], int randomNumber) {
    // Array per tracciare lo stato dei pulsanti e dei LED
    
        userNumber = 0;

        for (int i = 0; i < 4; i++) {
            int currentButtonState = digitalRead(buttonPins[i]);

            if (currentButtonState == LOW && lastButtonState[i] == HIGH) {
                ledState[i] = !ledState[i];
                digitalWrite(ledPins[i], ledState[i]);
            }
            lastButtonState[i] = currentButtonState;
        }

        for (int i = 0; i < 4; i++) {
            if (ledState[i] == HIGH) {
                userNumber |= (1 << i); 
            }
        }
        Serial.print("Numero inserito: ");
        Serial.println(userNumber);

       if (checkWin(userNumber, randomNumber))
       {
        changeState(ROUND_WIN);
       }
       

        delay(50); //Piccola pausa per evitare debounce
        
    return userNumber;
}

//Funzione di interrupt chiamata quando il bottone viene premuto
void wakeUpNow() {
  currRoundStartTime = 0;
  changeState(STARTUP);
}

void switchToRound(){
  changeState(PREPARE_ROUND);
}

void enableWakeUpInterrupts() {
  for(int i = 0; i < BUTTON_COUNT; i++) {
    enableInterrupt(buttonPins[i], wakeUpNow, RISING);
  }
}

void disableWakeUpInterrupts() {
  for(int i = 0; i < BUTTON_COUNT; i++) {
    disableInterrupt(buttonPins[i]);
  }
}
