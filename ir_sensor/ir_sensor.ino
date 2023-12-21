int pir = 13;
int gnd = 5;
int plb = 3;
int pin = 11;
int state;

void setup () {

    pinMode(pir,OUTPUT);
    pinMode(gnd,INPUT);
    pinMode(plb,OUTPUT);
    pinMode(pin,INPUT);
}

void loop () {
  digitalWrite(pir,HIGH);
  state = digitalRead(pin);
  digitalWrite(plb,state);
  delay(5000);
  
}
