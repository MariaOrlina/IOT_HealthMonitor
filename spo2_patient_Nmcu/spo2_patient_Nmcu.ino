#define BLYNK_TEMPLATE_ID "TMPLD56vrHpk"
#define BLYNK_DEVICE_NAME "Health Care"
#define BLYNK_AUTH_TOKEN "VWcRGXiN3QAqiD6Mrd1HJ8l1uHe4NQpT"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "shalom";      // Enter your Wifi Username
char pass[] = "marikit@2244";    // Enter your Wifi password

SimpleTimer timer;

int Selain = D7;
int Buzzer = D6;

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

int firstVal,secondVal,thirdVal,fourthVal,fifthVal; // sensors 

void myTimerEvent()
{
  Blynk.virtualWrite(V1, millis() / 1000);  
}

void setup()
{
  Serial.begin(9600);
  
  pinMode(Selain, INPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer,LOW);

  Blynk.begin(auth, ssid, pass);
  
  timer.setInterval(1000L,sensorvalue1); 
  timer.setInterval(1000L,sensorvalue2); 
  timer.setInterval(1000L,sensorvalue3);
  timer.setInterval(1000L,sensorvalue4);
  timer.setInterval(1000L,sensorvalue5);
  timer.setInterval(1000L,sensorvalue6);
}

void loop()
{
   if (Serial.available() == 0 ) 
   {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
   }
   
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
   //  Serial.println(myString); 
  // Serial.println("fahad");
// new code
String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2); 
String o = getValue(myString, ',', 3); 
String p = getValue(myString, ',', 4); 


firstVal = l.toInt();
secondVal = m.toInt();
thirdVal = n.toInt();
fourthVal = o.toInt();
fifthVal = p.toInt();

  myString = "";
    
    }
  }
}

void sensorvalue6()
{
 if(digitalRead(Selain) == LOW) 
  {
    Blynk.virtualWrite(V10, 0);
    delay(500);
  }
 else 
  {
    Blynk.virtualWrite(V10, 255);
    delay(500);
  }
}

void sensorvalue1()
{
 int sdata = firstVal;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, sdata);
}
void sensorvalue2()
{
int sdata = secondVal;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, sdata);
}
void sensorvalue3()
{
  int sdata = thirdVal;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V4, sdata);
}
void sensorvalue4()
{
  int sdata = fourthVal;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, sdata);
}
void sensorvalue5()
{
  int te = fifthVal;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V6, te);
  
  if (te > 50)
  {
  digitalWrite(Buzzer,HIGH);
  delay(500);
  }
  else
  {
  digitalWrite(Buzzer,LOW);
  delay(500);
  }
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
