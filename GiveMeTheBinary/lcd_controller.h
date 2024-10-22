#ifndef LCD_MANAGER
#define LCD_MANAGER
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

void initDisplay();
void writeOnLCD(const String firstLine, const String secondLine);
void clearLCD();

void turnOffLCD();
void turnOnLCD();

#endif