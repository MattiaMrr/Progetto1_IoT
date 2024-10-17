#include "game_controller.h"
#include "leds_controller.h"
#include "buttons_controller.h"
#include "constants.h"

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
}

// funzione per generare un numero random.
int generateRandomNumber()
{
  randomSeed(micros());
  int random_number = rand() % 16;
  return random_number;
}

int checkButton(int userNumber, int ledPins[], int randomNumber) {
     bool FLAG = true;
    // Array per tracciare lo stato dei pulsanti e dei LED
    

    while (FLAG == true) {
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
        FLAG = false;
       }
       

        delay(50); // Piccola pausa per evitare rimbalzi (debounce)
        
    }
    return userNumber;
}
