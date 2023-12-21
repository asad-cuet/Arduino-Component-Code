int value;
void setup() {

  pinMode(2,OUTPUT);
  pinMode(0, INPUT);
  
}
void loop() {
     value = digitalRead(0);
     digitalWrite(2,value);
     
}
