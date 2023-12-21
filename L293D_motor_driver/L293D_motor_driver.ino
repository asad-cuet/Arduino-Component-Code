#include<Servo.h>
Servo servo;
int motorAen=6;
int motorApin1= 12;
int motorApin2= 11;
int motorBen=5;
int motorBpin1= 3;
int motorBpin2= 2;
int i;
void setup() {
  servo.attach(9);
  pinMode(motorAen,OUTPUT);
  pinMode(motorApin1,OUTPUT);
  pinMode(motorApin2,OUTPUT);
  pinMode(motorBen,OUTPUT);
  pinMode(motorBpin1,OUTPUT);
  pinMode(motorBpin2,OUTPUT);      

}
void loop() {

    analogWrite(motorAen,255);
    analogWrite(motorBen,255);

  digitalWrite(motorApin1,HIGH);
  digitalWrite(motorApin2,LOW);
  digitalWrite(motorBpin1,LOW);
  digitalWrite(motorBpin2,HIGH);
  servo.write(0);
  delay(1000);
  servo.write(190);
  delay(2000);
  }
