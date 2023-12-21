int led = 12;
float value;
float volt;
void setup() {
  
Serial.begin(9600);
pinMode(led, OUTPUT);
}

void loop() {
value = analogRead(A0);
volt = (1024/5)*value;
Serial.println(volt);
if( value>512 && value<700) {
  digitalWrite(led, HIGH);
} else {
  digitalWrite(led,LOW);
}
  delay(50);
}
