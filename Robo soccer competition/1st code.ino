

int MotorA_in1 =2;
int MotorA_in2 =3;
int MotorB_in3 =4;
int MotorB_in4 =5;
int MotorA_PWM =9;
int MotorB_PWM =10;
char sms;

void setup() {
  Serial.begin(9600);
  pinMode(MotorA_in1, OUTPUT);
  pinMode(MotorA_in2, OUTPUT);
  pinMode(MotorB_in3, OUTPUT);
  pinMode(MotorB_in4, OUTPUT);
  pinMode(MotorA_PWM, OUTPUT);
  pinMode(MotorB_PWM, OUTPUT);

}
void loop() {
   analogWrite(MotorA_PWM, 252);
   analogWrite(MotorB_PWM, 252);

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

