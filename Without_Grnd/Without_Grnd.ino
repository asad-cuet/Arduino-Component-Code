int counter;
int x;
void setup() {
  for(x=1;x<=8;x++) {
    pinMode(x, OUTPUT);
    
  }
 
}
void loop() {
  digitalWrite(8,LOW);
  digitalWrite(1,HIGH);
}
