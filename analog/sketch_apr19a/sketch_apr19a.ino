int value;
int led = 12;

void setup () {

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  
}

void loop () {

  value = analogRead(A0);
  Serial.println(value);
  if (value <512) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
