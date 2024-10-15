#ifndef LCD_MANAGER
#define LCD_MANAGER
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

void initDisplay();
void writeOnLCD(const char* message);

#endif