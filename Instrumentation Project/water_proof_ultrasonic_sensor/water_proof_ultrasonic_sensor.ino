#include <NewPing.h> // Library for ultrasonic sensors


int TRIGGER_PIN= 12; // The pin connected to the trigger pin of the ultrasonic sensor
int ECHO_PIN= 13;    // The pin connected to the echo pin of the ultrasonic sensor
int maxDistance=1000;


NewPing sonar(TRIGGER_PIN, ECHO_PIN, maxDistance); // Create an instance of the NewPing class


void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging (optional)
}


void loop() {
  unsigned int distance = sonar.ping_cm(); // Send a ping and get the distance in centimeters
  Serial.print(distance);
  if (distance) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm"); // Print the distance to the serial monitor
  }

//  delay(1000); // Wait for a second before taking another reading
}
