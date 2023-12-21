#include <IRremote.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

int state1=1;
int state2=1;
int state3=1;
int led1=8;
int led2=9;
int led3=10;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);  
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);    
    irrecv.resume(); // Receive the next value
  
    
    if(results.value == 0x24DB8877)
    {
     digitalWrite(led1,state1);
     state1 = !state1; 
    }
    if(results.value == 0x24DB48B7)
    {
     digitalWrite(led2,state2);
     state2 = !state2; 
    }
    if(results.value == 0x24DBC837)
    {
     digitalWrite(led3,state3);
     state3 = !state3; 
    }
    
    
  }   
  

}
