

int const trigpin=7;
int const echopin=6;
int const buzpin=2;
int duration,distance;

void setup ()
{
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(buzpin,OUTPUT);
}

void loop() 
{
  digitalWrite(trigpin,HIGH);
  delay(1);
  digitalWrite(trigpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance=(duration/2)/29.1;
  if (distance<=50 && distance>=0) {
    digitalWrite(buzpin,HIGH);} else {
      digitalWrite(buzpin,LOW);}\
      delay(60);
      
  }
