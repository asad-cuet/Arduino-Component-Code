#include <Wire.h>
#include <NewPing.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();


#define BUZZER_PIN 5
#define CUT_OFF_TEMPERATURE 30  //This is temperature in degreeC
#define DISTANCE_TO_CHECK 10    //This is in cm

NewPing ultrasonicSensor(2,3,400);

void setup() 
{
  analogWrite(BUZZER_PIN, 0);
  Serial.begin(9600);
  mlx.begin();
}

void tempHighTone() 
{ 
  for (int i = 0; i < 10; i++)
  {
    analogWrite(BUZZER_PIN,100);
    delay(100);
    analogWrite(BUZZER_PIN,0);
    delay(100);  
  }      
}

void tempOkTone() 
{ 
  analogWrite(BUZZER_PIN, 100);
  delay(2000);
  analogWrite(BUZZER_PIN, 0);
}

void loop() 
{
  int distance = ultrasonicSensor.ping_cm();
  Serial.print("Distance");
  Serial.println(distance);
  if (distance > 0 && distance < DISTANCE_TO_CHECK)
  {
    delay(2000);
    float temperature = mlx.readObjectTempC();
    Serial.print("Temperature");
    Serial.println(temperature);
    distance = ultrasonicSensor.ping_cm();
    if (distance > 0 && distance < DISTANCE_TO_CHECK && temperature <= CUT_OFF_TEMPERATURE)
    {
      tempOkTone();
      delay(2000);
    }
    else if ( !(distance > 0 && distance < DISTANCE_TO_CHECK))
    {
    }
    else
    {
      tempHighTone();
      delay(2000);
    }
  }
}
