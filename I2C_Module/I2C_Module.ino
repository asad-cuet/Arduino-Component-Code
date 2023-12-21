#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  lcd.begin();
}

void loop() {


  lcd.setCursor(0,0);
  lcd.print("I2C Module system");
  lcd.setCursor(0,1);
  lcd.print("Used");
}
