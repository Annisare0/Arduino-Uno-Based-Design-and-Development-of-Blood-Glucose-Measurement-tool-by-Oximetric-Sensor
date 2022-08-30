#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
 
LiquidCrystal_I2C lcd(0x27,16,2);
 
#define REPORTING_PERIOD_MS     1000
#define  IR_LED_CURRENT         0x05 // 27.1 mA
#define RED_LED_CURRENT         0x05 // 37 mA 0x0B

int red,ir;
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
 
void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
 
    lcd.init()
    ;lcd.backlight();
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
    lcd.begin(16,2);
    lcd.print("Initializing...");
    delay(3000);
    lcd.clear();
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
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
    // Make sure to call update as fast as possible
    pox.update();
     
      float R = (110-float(pox.getSpO2()))/25;
     if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        float glu = ((214.11*R)-10.033

);
        Serial.print("SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
        Serial.print(R);
        Serial.print("\t");
        Serial.print("glu=");
        Serial.print(glu);
        Serial.println(" mg/Dl");

        
    uint16_t ir, red;
  
        lcd.clear();
        lcd.setCursor(0,0);
          if (millis() >20000) {
        lcd.print("Glu: ");
        lcd.setCursor(5,0);
        lcd.print(glu);
        lcd.setCursor(9,0);
        lcd.print("mg/dL");
        lcd.setCursor(0,1);
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.print("%");
    
 }
        tsLastReport = millis();
    }
}
