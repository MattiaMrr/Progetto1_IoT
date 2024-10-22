#include "lcd_controller.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Arduino.h>

// the object to access the lcd.
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Initialize the display.
void initDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

// Function that writes on display. Arguments are first and second line to write on the lcd.
void writeOnLCD(const String firstLine, const String secondLine) {
  lcd.setCursor(0, 0);
  lcd.print(firstLine);
  //Serial.print("firstLine: ");
  //Serial.println(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
  //Serial.print("secondLine: ");
  //Serial.println(secondLine);
}

// Clear lcd.
void clearLCD() {
  lcd.clear();
}

void turnOffLCD() {
  lcd.noBacklight();
  lcd.off();
}
void turnOnLCD() {
  lcd.on();
  lcd.backlight();
}

