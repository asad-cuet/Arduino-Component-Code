
int trig = 13;    // sonar sensor
int echo = 12;
float distance,duration;
int MotorA_in1 =2;
int MotorA_in2 =3;
int MotorB_in3 =4;
int MotorB_in4 =5;
int MotorA_PWM =9;
int MotorB_PWM =10;
char sms;
int spd= 150;
void setup() {
  Serial.begin(9600);
  pinMode(MotorA_in1, OUTPUT);
  pinMode(MotorA_in2, OUTPUT);
  pinMode(MotorB_in3, OUTPUT);
  pinMode(MotorB_in4, OUTPUT);
  pinMode(MotorA_PWM, OUTPUT);
  pinMode(MotorB_PWM, OUTPUT);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}
void loop() {
   analogWrite(MotorA_PWM, spd);
   analogWrite(MotorB_PWM, spd);
   Sonarsensor();
   if(Serial.available()) {
   sms = Serial.read();
   }
   if(sms == 'B') {
    RobotBackward();
   }
   if(sms == 'F') {
    RobotForward();
   }
   if(sms == 'R') {
    RobotRight();
   }
   if(sms == 'L') {
    RobotLeft();
   }
      if(sms == 'S') {
    RobotStop();
   }
   if(sms == '0') {
    spd = 0;
   }
      if(sms == '1') {
    spd = 28;
   }
      if(sms == '2') {
    spd = 56;
   }
      if(sms == '3') {
    spd = 84;
   }
      if(sms == '4') {
    spd = 112;
   }
      if(sms == '5') {
    spd = 140;
   }
      if(sms == '6') {
    spd = 168;
   }
      if(sms == '7') {
    spd = 196;
   }
      if(sms == '8') {
    spd = 224;
   }
      if(sms == '9') {
    spd = 252;
   }
   }
void RobotForward() {
  digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, HIGH);
  digitalWrite(MotorB_in3, HIGH);
  digitalWrite(MotorB_in4, LOW);

}

void RobotStop() {
  
  digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, LOW);
}

void RobotBackward() {
  digitalWrite(MotorA_in1, HIGH);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, HIGH);
}


void RobotRight() {
    digitalWrite(MotorA_in1, HIGH);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, HIGH);
  digitalWrite(MotorB_in4, LOW);
}

void RobotLeft() {
    digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, HIGH);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, HIGH);
  
}
void Sonarsensor(){
        digitalWrite(trig, LOW);
        delay(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig,LOW);
        duration =pulseIn(echo, HIGH); 
        distance=(duration*0.0332)/2;  // calculated in cm
        Serial.print("distance is=");
        Serial.print(distance);
        Serial.print("\n");
}  
