#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3); // RX, TX pins for Bluetooth module

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available()) {
    char data = bluetooth.read();
    Serial.print("Received: ");
    Serial.println(data);
  }

  // Send data to mobile device
  bluetooth.print("Hello from Arduino!");
  Serial.println("Data Sent");
  delay(1000); // Delay for stability
}
