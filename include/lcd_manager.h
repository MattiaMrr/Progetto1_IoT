#ifndef LCD_MANAGER
#define LCD_MANAGER
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

/*Funzione che inizializza lo schermo LCD.*/
void initDisplay();

/*Funzione che permette di scrivere sullo schermo LCD.*/
void writeOnLCD(const String firstLine, const String secondLine);

/*Fuzione che pulische lo schermo.*/
void clearLCD();

#endif