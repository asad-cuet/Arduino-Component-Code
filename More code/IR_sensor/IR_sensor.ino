int const out=6;
int const light=10;

void setup() {
  pinMode(out,INPUT);
  pinMode(light,OUTPUT);
  
}

void loop() {
  if (out == HIGH) {
    digitalWrite(light,HIGH);} else {
      digitalWrite(light,LOW);}
      delay(60000);
  }
