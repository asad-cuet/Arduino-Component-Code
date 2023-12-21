#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
 
#define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
uint32_t tsLastReport = 0;



#include <LiquidCrystal.h>
#include <dht.h>

dht DHT;

#define DHT22_PIN 5

//pin
const int ok = A1;
const int UP = A2;
const int DOWN = A3;

const int bulb = 3;
const int vap = 6;

const int rs = 13;
const int en = 12;
const int d4 = 11;
const int d5 = 10;
const int d6 = 9;
const int d7 = 8;


//variable
int currentHimudity=0;
int currentTemp=0;
int oldHimudity=0;
int oldTemp=0;
int T_threshold = 30;
int H_threshold = 60;
int SET = 0;
int loop_no=0;
boolean T_condition = true;
boolean H_condition = true;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup()
{
    pinMode(ok, INPUT);
    pinMode(UP, INPUT);
    pinMode(DOWN, INPUT);
    pinMode(bulb, OUTPUT);
    pinMode(vap, OUTPUT);


    digitalWrite(bulb, LOW);
    digitalWrite(vap, LOW);
    digitalWrite(ok, HIGH);
    digitalWrite(UP, HIGH);
    digitalWrite(DOWN, HIGH);



    lcd.begin(16, 2);
    Serial.begin(9600);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperature &");
    lcd.setCursor(0,1);
    lcd.print("Humidity ");
    delay (3000);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Controller For");
    lcd.setCursor(0,1);
    lcd.print("Incubator");
    delay (3000);


    //pulse
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
void loop()
{
    // while(1)
    // {
    //   if (digitalRead(ok) == LOW)
    //   {
    //     Serial.println("ok");
    //     delay(100);
    //   }
    // }
  

  //clear
  if (SET == 0)
  {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Temperature:");
      lcd.setCursor(0, 1);
      lcd.print(T_threshold);
      lcd.print(" *C");

      Serial.println("Set Temperature:");



      while (T_condition)
      {
        if (digitalRead(UP) == LOW)
        {
          T_threshold = T_threshold + 1;
          lcd.setCursor(0, 1);
          lcd.print(T_threshold);
          lcd.print(" *C");
          Serial.print(T_threshold);
          Serial.println(" *C");
          delay(200);
        }
        if (digitalRead(DOWN) == LOW)
        {
          T_threshold = T_threshold - 1;
          lcd.setCursor(0, 1);
          lcd.print(T_threshold);
          lcd.print(" *C");
          Serial.print(T_threshold);
          Serial.println(" *C");
          delay(200);
        }
        if (digitalRead(ok) == LOW)
        {
          delay(200);
          T_condition = false;
        }
      }



      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Humidity:");
      Serial.println("Set Humidity:");
      lcd.setCursor(0, 1);
      lcd.print(H_threshold);
      lcd.print("%");
      delay(100);



      while (H_condition)
      {
        if (digitalRead(UP) == LOW)
        {
          H_threshold = H_threshold + 1;
          lcd.setCursor(0, 1);
          lcd.print(H_threshold);
          lcd.print("%");
          Serial.print(H_threshold);
          Serial.println(" %");
          delay(100);
        }
        if (digitalRead(DOWN) == LOW)
        {
          H_threshold = H_threshold - 1;
          lcd.setCursor(0, 1);
          lcd.print(H_threshold);
          lcd.print("%");
          Serial.print(H_threshold);
          Serial.println(" %");
          delay(200);
        }
        if (digitalRead(ok) == LOW)
        {
          delay(100);
          H_condition = false;
        }
      }
      SET = 1;
      lcd.clear();
  }

  if(loop_no==0)
  {
    lcd.clear();
  }
  loop_no++;
  
  // DISPLAT DATA
  currentHimudity=int(getHumidity());
  currentTemp=getTemperature();

  Serial.print("Temperature:");
  Serial.println(currentTemp);
  Serial.print("Humidity:");
  Serial.println(currentHimudity);
  if(currentHimudity!=oldHimudity)
  {
    lcd.setCursor(0, 0);
    lcd.print("Humidity:");
    lcd.setCursor(10, 0);
    lcd.print(getHumidity());
    lcd.setCursor(12, 0);
    lcd.print("%  ");
  }


    if(currentTemp!=oldTemp)
    {
      lcd.setCursor(0, 1);
      lcd.print("Temp: ");
      lcd.setCursor(6, 1);
      lcd.print(getTemperature());
      lcd.setCursor(8, 1);
      lcd.print("*C  ");
    }



    Serial.print("DHT11, \t");
    Serial.print(getTemperature(),1);
    Serial.print(",\t");
    Serial.println(getHumidity(),1);
    delay(100);

    //bulb, vap logic
    if (1)
    {
        if(getTemperature() < T_threshold)
        {
            delay(500);
            if (getTemperature() < T_threshold)
            {
              digitalWrite(bulb, HIGH);
              Serial.println("Bulb High");
            }
        }
        if (getTemperature() >= T_threshold)
        {
            delay(500);
            if (getTemperature() >= T_threshold)
            {
              digitalWrite(bulb, LOW);
              Serial.println("Bulb Low");
            }
        }
        if (getHumidity() >= H_threshold)
        {
            delay(500);
            if (getHumidity() >= H_threshold)
            {
              digitalWrite(vap, HIGH);
              Serial.println("Vap High");
            }
        }

        if (getHumidity() < H_threshold)
        {
            delay(500);
            if (getHumidity() < H_threshold)
            {
              digitalWrite(vap, LOW);
              Serial.println("Vap Low");
            }
        }
    }
    else
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("No Sensor data.");
        lcd.setCursor(0, 1);
        lcd.print("System Halted.");
        Serial.println("No Sensor Data");
        digitalWrite(bulb, LOW);
        digitalWrite(vap, LOW);
    }
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
 
        tsLastReport = millis();
    }
}

float getTemperature()
{
  int chk = DHT.read11(DHT22_PIN);
  return DHT.temperature;
}

float getHumidity()
{
  int chk = DHT.read11(DHT22_PIN);
  return DHT.humidity;
}

void onBeatDetected()
{
    Serial.println("Beat!");
}
 
