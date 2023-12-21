#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  mlx.begin();
}

void loop() {
  float tempC = mlx.readObjectTempC();
  float tempF = mlx.readObjectTempF();
  
  Serial.print("Object Temperature (C): ");
  Serial.print(tempC);
  Serial.print("   ");

  Serial.print("Object Temperature (F): ");
  Serial.println(tempF);

  delay(1000); // Delay for a second
}
