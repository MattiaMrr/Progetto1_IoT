#include "lcd_manager.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void writeOnLCD(const char* firstLine, const char* secondLine) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstLine);
  Serial.print("firstLine: ");
  Serial.println(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
  Serial.print("secondLine: ");
  Serial.println(secondLine);
}

