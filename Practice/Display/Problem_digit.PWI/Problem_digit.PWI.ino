#include<LiquidCrystal.h>
LiquidCrystal lcd(13,11,7,6,5,4);
int i;
void setup() {
  lcd.begin(20,4);
  Serial.begin(9600);
}
void loop() {

  lcd.setCursor(3,1);
  lcd.print("Engineer Asad");


  for(i=1;i<=99;i++) {
    lcd.setCursor(0,0);
    lcd.print(i/10);
    lcd.setCursor(1,0);
    lcd.print(i%10); 
    Serial.print(i);  
    delay(500);
  }
  
}
