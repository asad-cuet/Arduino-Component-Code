#include<LiquidCrystal.h>;
LiquidCrystal lcd(7,6,5,4,3,2);
float value;
int milivolt;
float temp;


void setup() {

  lcd.begin(20,4);
}
void loop () {

  value = analogRead(A0);
  milivolt=(value*5000)/1024;
  temp=milivolt/10;
  lcd.setCursor(0,0);
  lcd.print("Digital Thermometer");
  lcd.setCursor(2,1);
  lcd.print("Temperatue=");
  lcd.print(temp);
  lcd.print(char(223));
  lcd.print("c");
  
}
