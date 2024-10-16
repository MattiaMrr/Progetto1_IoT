#include "lcd_manager.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void writeOnLCD(const char* message) {
    lcd.print(message);
}

