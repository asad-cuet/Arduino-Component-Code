int trig = 12;
int echo = 13;
float distance,duration;

void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    Serial.begin(9600);
    
}

void loop() {

  digitalWrite(trig, HIGH);
  delay(0.01);
  digitalWrite(trig, LOW);
  duration =pulseIn(echo, HIGH); // duration=High hoye Low howa porjonto shomoi //
  distance=duration*0.0332/2;
  Serial.println("Distance=");
  Serial.println(distance);
  Serial.print("cm");
  
}
