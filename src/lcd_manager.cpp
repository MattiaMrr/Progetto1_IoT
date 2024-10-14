#include <lcd_manager.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void go_message() {
lcd.init();
lcd.backlight();
lcd.print("Let's go");
}