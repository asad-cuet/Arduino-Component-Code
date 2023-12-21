#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address (0x27 for a common 20x4 display)
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();  // Turn on the backlight
  lcd.setCursor(0, 0);  // Set cursor to the first line
  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);  // Set cursor to the second line
  lcd.print("I2C LCD Example");
}

void loop() {
  // Your loop code here
}
