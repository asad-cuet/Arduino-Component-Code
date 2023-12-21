#include<Servo.h>
Servo survo;
int i;
void setup() {
  survo.attach(6);
}
void loop() {
  for(i=0;i<=205;i=i+5) {
  survo.write(i);
  delay(5);
  if(i==205) {
    for(i=205;i>=0;i=i-5) {
      survo.write(i);
      delay(5);
    }
  }

  } 
}
