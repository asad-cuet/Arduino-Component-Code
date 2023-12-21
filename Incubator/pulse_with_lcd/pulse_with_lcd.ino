#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#include <LiquidCrystal.h>
const int rs = 13;
const int en = 12;
const int d4 = 11;
const int d5 = 10;
const int d6 = 9;
const int d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
#define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
 
void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
  
    Serial.begin(9600);
    Serial.print("Initializing pulse oximeter..");

    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Pulse Oximeter");
    delay(2000);
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
    lcd.clear();
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop()
{
    // Make sure to call update as fast as possible
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");

        
//        lcd.setCursor(0,0);
//        lcd.print("Heart rate:");
//        lcd.setCursor(11,0);
//        lcd.print(pox.getHeartRate());

        lcd.setCursor(0,0);
        lcd.print("SpO2:");
        lcd.setCursor(6,0);
        lcd.print(pox.getSpO2());
        lcd.setCursor(9,0);
        lcd.print("%");

        tsLastReport = millis();
    }
}
