#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <DHT.h>

#define REPORTING_PERIOD_MS     1000

#define DHTPIN 7
#define DHTTYPE DHT11

float temp;

PulseOximeter pox;

DHT dht(DHTPIN, DHTTYPE);

uint32_t tsLastReport = 0;

int sdata1 = 0; // sensor1 data
int sdata2 = 0; // sensor2 data
int sdata3 = 0; // sensor3 data
int sdata4 = 0; // sensor4 data
int sdata5 = 0; // sensor5 data

String cdata; // complete data, consisting of sensors values

void onBeatDetected()
{
  Serial.println("Beat!");
}

void setup()
{
    Serial.begin(9600);

    Serial.print("Initializing pulse oximeter..");

    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    pox.setOnBeatDetectedCallback(onBeatDetected);
    
  dht.begin();
    
}

void loop()
{
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  temp = analogRead(A0);
  temp = temp*(5/1023.0)*100;

    pox.update();   

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) 
    {
      cdata = cdata + sdata1+","+sdata2+","+sdata3+","+sdata4+","+sdata5; // comma will be used a delimeter
      Serial.println(cdata); 
      cdata = ""; 
        
        //Serial.print("Heart rate:");
        //Serial.print(pox.getHeartRate());
        //Serial.print("bpm / SpO2:");
        //Serial.print(pox.getSpO2());
        //Serial.println("%");
         sdata1 = pox.getHeartRate(); 
         sdata2 = pox.getSpO2();
        //Serial.print("Humidity :");
        //Serial.println(h);
         sdata3 = h;
        //Serial.print("Temperature");
        //Serial.println(t);
         sdata4 = t;
        //Serial.print("Temp: ");
        //Serial.println(temp);
         sdata5 = temp;
        //Serial.println("*********************************");
        //Serial.println();
 
        tsLastReport = millis();
    }
}
