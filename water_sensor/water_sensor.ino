
int availablePerc=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lower_read=analogRead(A0);
  int upper_read=analogRead(A1);
  int sensitivity=950;
  if(lower_read<950)
  {
    Serial.println("water low");
  }
  if(lower_read>sensitivity && upper_read<sensitivity)
  {
    Serial.println("water filled");
  }
  if(upper_read>sensitivity && lower_read>sensitivity)
  {
    Serial.println("water over filled");
  }
  Serial.print("lower_read: ");
  Serial.println(lower_read);
  Serial.print("upper_read: ");
  Serial.println(upper_read);
  delay(1000);
  // Serial.println("sensed");
}

void mesaureWaterPerc()
{
  if(digitalRead(A0)==LOW)
  {
    Serial.println("water low");
    availablePerc=0;
  }
  if(digitalRead(A0)==HIGH && digitalRead(A1)==LOW)
  {
    Serial.println("water filled");
    availablePerc=50;
  }
  if(digitalRead(A1)==HIGH && digitalRead(A0)==HIGH)
  {
    Serial.println("water over filled");
    availablePerc=100;
  }
  Serial.print("A0: ");
  Serial.println(digitalRead(A0));
  Serial.print("A1: ");
  Serial.println(digitalRead(A1));

}
