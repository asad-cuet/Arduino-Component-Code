int MotorA_in1 =2;
int MotorA_in2 =3;
int MotorB_in3 =4;
int MotorB_in4 =5;
int MotorA_PWM =9;
int MotorB_PWM =10;

void setup() {
  pinMode(MotorA_in1, OUTPUT);
  pinMode(MotorA_in2, OUTPUT);
  pinMode(MotorB_in3, OUTPUT);
  pinMode(MotorB_in4, OUTPUT);
  pinMode(MotorA_PWM, OUTPUT);
  pinMode(MotorB_PWM, OUTPUT);
}
void loop() {
  
  analogWrite(MotorA_PWM, 255);
  analogWrite(MotorB_PWM, 255);
//Robot forward
  digitalWrite(MotorA_in1, HIGH);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, HIGH);
  delay(4000);

  // robot stop
  
  digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, LOW);
  delay(3000);

  //robot backward
  digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, HIGH);
  digitalWrite(MotorB_in3, HIGH);
  digitalWrite(MotorB_in4, LOW);
  delay(3000);
    // robot stop
  
  digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, LOW);
  delay(3000);

  //Robot turn Right
    digitalWrite(MotorA_in1, LOW);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, HIGH);
  delay(3000);

  //Robot turn left
    digitalWrite(MotorA_in1, HIGH);
  digitalWrite(MotorA_in2, LOW);
  digitalWrite(MotorB_in3, LOW);
  digitalWrite(MotorB_in4, LOW);
  delay(3000);
}
