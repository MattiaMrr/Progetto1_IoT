#ifndef LEDS_CONTROLLER_H
#define LEDS_CONTROLLER_H

#include "constants.h"

#define DEFAULT_FADE_AMOUNT 17
#define START_INTENSITY 0

/*Funzione che inizializza i led.*/
void initLeds(int ledPins[]);

/*Funzione che spegne un pin.*/
void turnOffLed(int ledPin);

/*Funzione che accende un led.*/
void turnOnLed(int ledPin);

/*Funzione che accende tutti i led verdi.*/
void turnOnGreenLeds(int ledPins[]);

/*Funzione che spegne tutti i led verdi.*/
void turnOffGreenLeds(int ledPins[]);

/*Funzione che accende il led rosso.*/
void turnOnRedLed();

/*Funzione che spegne il led rosso.*/
void turnOffRedLed();

/*Funzione che fa pulsare il led rosso.*/
void pulseRedLed();

/*Funzione che spegne tutti i led sulla board.*/
void resetBoard(int ledPins[]);

/*Funzione che tramite i led mostra la difficoltà selezionata.*/
void showDifficulty(int difficulty, int ledPins[]);

#endif // LEDS_CONTROLLER_H