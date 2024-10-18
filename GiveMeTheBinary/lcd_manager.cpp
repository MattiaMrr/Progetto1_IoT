#include "lcd_manager.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void writeOnLCD(const char* firstLine, const char* secondLine) {
    lcd.setCursor(0, 1);
    lcd.print(firstLine);
    lcd.setCursor(0, 2);
    lcd.print(secondLine);
}

