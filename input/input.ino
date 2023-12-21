int led = 13;
int inp = 5;
int state;

void setup () {

     pinMode(led,OUTPUT);
     pinMode(inp,INPUT);
     
}
 void loop() {
   state = digitalRead(inp);
   digitalWrite(led,state);
 }
