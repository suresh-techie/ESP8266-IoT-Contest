# ESP8266-IoT-Contest


          //IoT Based Garden Automation And Monitoring System
  
#include <CayenneEthernet.h>
#define CAYENNE_PRINT Serial    // Comment this out to disable prints and save space
#include <CayenneMQTTESP8266.h>
#include <SPI.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 7

// WiFi network info.
char ssid[] = "ssid";
char wifiPassword[] = "wifiPassword";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "MQTT_USERNAME";
char password[] = "MQTT_PASSWORD";
char clientID[] = "CLIENT_ID";

unsigned long lastMillis = 0;

#define VIRTUAL_PIN1 V1
#define VIRTUAL_PIN2 V2
#define VIRTUAL_PIN3 V3
#define VIRTUAL_PIN4 V4
#define VIRTUAL_PIN5 V5


const int VAL_PROBE = 0; //Analog pin 0
const int MOISTURE_LEVEL = 250; // the value after the LED goes on

int sensorValue; 
int relay = 6;
int pumpLed   = 13;
//Sunlight
const int pinLight = A1;
const int pinLed   = 7;


void setup()
{
  
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(pumpLed, OUTPUT);
  delay(1000);
}

void loop()
{
  Cayenne.loop();
}

CAYENNE_OUT(VIRTUAL_PIN1)
{    //Moisture Readings
   int moisture = analogRead(VAL_PROBE);
   delay(500);  
   int  Moisture=moisture;  
   Serial.print("\n >>>>>Moisture:");
   Serial.print(Moisture);
   Serial.print("%");
     Cayenne.virtualWrite(VIRTUAL_PIN1, Moisture);
}
CAYENNE_OUT(VIRTUAL_PIN2)
{    
    //Sunlight Readings
  int sensor = analogRead(pinLight);
  int sunlight = map(sensor,1023, 0,0,100);
  int Sunlight=sunlight;
   delay(500);
     Serial.print(" \n >>>>Sunlight:");
     Serial.print(Sunlight);
 
     Cayenne.virtualWrite(VIRTUAL_PIN2, Sunlight);
}
CAYENNE_OUT(VIRTUAL_PIN3)
{    //Temperature Readings
  int chk = DHT.read11(DHT11_PIN);
  Serial.print(" \n >>>>>Temperature:");
  Serial.print(DHT.temperature);
  Serial.print("C");
  int t=DHT.temperature;
 
     Cayenne.virtualWrite(VIRTUAL_PIN3, t);
}
CAYENNE_OUT(VIRTUAL_PIN4)
{     //Humidity Readings
  int chk = DHT.read11(DHT11_PIN);
  Serial.print(" \n>>>>>> Humidity:");
  Serial.print(DHT.humidity);
  Serial.print("%");
  int h=DHT.humidity;
     Cayenne.virtualWrite(VIRTUAL_PIN4, h);
}
CAYENNE_IN(VIRTUAL_PIN5)
{
  // get value sent from dashboard
  int currentValue = getValue.asInt(); // 0 to 1
  Serial.println(currentValue);
  // assuming you wire your relay as normally open
  if (currentValue == 0) {
    digitalWrite(pumpLed, HIGH);
  } else {
    digitalWrite(pumpLed, LOW);
  }
}
