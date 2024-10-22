#include <Arduino.h>
#include "init.h"
#include "constants.h"
#include "leds_controller.h"
#include "game_controller.h"
#include "potentiometer_controller.h"
#include "lcd_manager.h"

#include <avr/sleep.h>

extern const int BTN_PINS[];
extern const int LED_PINS[];

extern double factor;
extern double roundTime;
extern int score;
extern int state;

void setup() {
  // Initialize buttons, leds and display.
  initAll();

  // Generates a random seed for the random() function.
  setupSeed();

  // Initialize Serial line.
  Serial.begin(9600);

  // First state is STARTUP.
  changeState(STARTUP);

  // Reset the board leds to make sure everything is off.
  resetBoard();

  // Enable the interrupt to switch from STARTUP to 
  enableStartInterrupt();
}

// Superloop
void loop() {
  // Actions change depending on the state
  switch (state) {
    case STARTUP:
      /* When in startup state, the game pulses the red led and reads the potentiometer to select the difficulty.
        As the potentiometer is turned the difficulty level is shown on leds.
        After 20 seconds are elapsed the game goes into DEEP_SLEEP, instead if the user click BTN1 the game starts.
      */
      int newDifficulty; 

      // Enable interrupts TODO: check if really needed.
      interrupts();

      // Pulse red led.
      pulseRedLed();

      // Write the welcome message on the LCD.
      writeOnLCD("Welcome to GMB!", "Press B1 to Start");

      // Read difficulty from potentiometer.
      newDifficulty = readDifficulty();

      // Check if difficulty had changed and if so show the new difficulty on the LEDS.
      if (newDifficulty != difficulty) {
        Serial.print("DIFFICULTY ");
        Serial.println(newDifficulty);
        setDifficulty(newDifficulty);
        showDifficulty(newDifficulty);
      }
      
      // If more than 20 seconds are elapsed within this state, change state to DEEP_SLEEP. TODO: dont use magic number.
      if (millis() - currRoundStartTime >= 20000) {
        Serial.println("20 seconds");
        // Change the state.
        changeState(DEEP_SLEEP);
        // Clears the LCD.
        clearLCD();
        // Disable the interrupt attached on BTN1 to switch state to PREPARE_ROUND. New interrupts will be enabled inside the deep sleep state.
        disableStartInterrupt();
      }
      break;
    case DEEP_SLEEP:
      /*
        Inside the deep sleep state the machine is basically turned off to save power.
        When an interrupt occurs it is woken up and goes back to STARTUP state.
      */
      // Enables interrupts to wake up on all 4 buttons.
      enableWakeUpInterrupts();
      // Makes sure to have interrupts enabled. TODO: check if really needed.
      interrupts();
      // Turn off the leds before going to sleep.
      resetBoard();
      turnOffLCD();
      // Code to go to sleep.
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();
      // Wakes up here, first thing to do is disable the sleep mode.
      sleep_disable();
      // And then disable the interrupts for the wakeup.
      disableWakeUpInterrupts();
      // Finally change state back to STARTUP.
      turnOnLCD();
      difficulty = 0;
      changeState(STARTUP);
      // Also enable the interrupt to switch to PREPARE_ROUND since it was disabled before the deep sleep.
      enableStartInterrupt();
      // Disables the interrupts: TODO: i dont really understand this but it works.
      noInterrupts();
      break;
    case PREPARE_ROUND:
      /*
        A state that does all the preparation needed for the start of the next round.
        Writes GO!!! on the lcd, then fenerates the random number to be translated in binary by the user and waits
        2 seconds before showing it on the lcd display.
      */
      int rand_num;

      // Disable the interrupt that got us here, not needed anymore.
      disableStartInterrupt();

      clearLCD();

      // Write GO on the lcd.
      writeOnLCD("GO!!!", "");

      // LED animation??
      //...

      // Since no LED animation and no input i can just delay.
      delay(2000);
      // Generate random number.
      rand_num = generateRandomNumber();

      Serial.print("gen num:");
      Serial.println(rand_num);

      // Write the random number on the lcd.
      clearLCD();
      writeOnLCD("Number: ", String(rand_num));

      // Change state to ROUND.
      changeState(ROUND);
      break;
    case ROUND:
      /*
        Inside the round state the user input on the buttons is read by the program and used to turn on/off the leds.
        After a certain time (decreased after every successfull round) the input is checked and if the user guessed the binary 
        version of the number switched state to either ROUND_WIN or GAME OVER.
      */

      // Read user input on the buttons.
      readButtons();

      // Serial.print("time in round: ");
      // Serial.println(millis() - currRoundStartTime);

      // After a certain time check the guess and change state.
      if (millis() - currRoundStartTime >= roundTime) {
        // readLedStatesAsInt reads the current status of the leds and translates it to an int, which is checked by checkWin that returns a true if the num is correct.
        changeState(checkWin(readLedStatesAsInt()) ? ROUND_WIN : GAME_OVER);
      }
      
      break;
    case ROUND_WIN:
      /*
        This is the state inbetween rounds. When the user guesses the number the score
        is increased and writted on the lcd, then generates the next number to be translated.
      */
      // Increase score.
      score++;
      
      // Show score on LCD.
      clearLCD();
      writeOnLCD("GOOD!", String("Score: ") + String(score));

      // Wait 2 seconds for user to the score.
      delay(2000);

      // Generate next random TODO: usa funzione per evitare ripetizioni di codice.
      rand_num = generateRandomNumber();

      // Calculate time for the next round, it is multiplied by a factor <= 1 that reduces the time available. it depends on the diffculty.
      updateRoundTime();

      // Write next number on lcd.
      clearLCD();
      writeOnLCD("Number: ", String(rand_num));

      // Change state.
      changeState(ROUND);
      break;
    case GAME_OVER:
      /*
        When the user guesses wrong, the game is over, a red led is on for 2 seconds while the final score in written on the lcd.
      */
      // A red led is on ONLY FOR THE FIRST SECOND, then it stays off.
      if (millis() - currRoundStartTime >= 1000) {
        turnOffRedLed();
      } else {
        turnOnRedLed();
      }

      // Write info on lcd.
      writeOnLCD("Game Over", String("Final Score: ") + String(score));

      // After 10 seconds start over.
      if (millis() - currRoundStartTime >= 10000) {
        Serial.println("Restarting...");

        // Reset score and difficulty.
        score = 0;
        difficulty = 0;

        // Go back to STARTUP state and enable the interrupt needed in that state.
        changeState(STARTUP);
        enableStartInterrupt();
      }

      break;
  }
}
