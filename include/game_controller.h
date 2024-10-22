#include <Arduino.h>

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

extern int state;
extern unsigned long int currRoundStartTime;
extern unsigned long difficulty;
extern int random_number;

/*Funzione che cambia lo stato dello switch.*/ 
void changeState(int newState);

/*Funzione per generare un numero random.*/ 
int generateRandomNumber();

/*Funzione per controllare se il round e' stato vinto*/ 
bool checkWin(int user_num, int rand_num);

/*Funzione che controlla il numero inserito tramite i bottoni e lo salva dentro la variabile userNumber.*/ 
int checkButton(int ledPins[], int randomNumber);

/* Funzione di interrupt chiamata quando il bottone viene premuto*/
void wakeUpNow();

/* Funzione che cambia a lo stato a prepare round.*/
void switchToRound();

/* Funzione che tramite l'interrupt sveglia arduino dal deep sleep.*/
void enableWakeUpInterrupts();

/*Funzione che disattiva gli interrupt.*/ 
void disableWakeUpInterrupts();

/*Funzione che azzera i led e bottoni.*/ 
void resetButtonsAndLeds(int buttonPins[], int ledPins[]);

/*Funzione che imposta il seed.*/ 
void setupSeed();

#endif // GAME_CONTROLLER_H