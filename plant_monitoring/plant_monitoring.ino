#define BLYNK_PRINT Serial   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D2



OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char auth[] ="G-nd5LTwt8_-en8gK9z9OD0OBC2Xv9wJ";               //Authentication code sent by Blynk
char ssid[] = "SHAIK SUBHANI";                       //WiFi SSID
char pass[] = "9390539087";                       //WiFi Password

#define sensorPin D3 
int sensorState = 0;
int lastState = 0;
#define DHTPIN D2    
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
}
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
   pinMode(sensorPin, INPUT);
  dht.begin();

  timer.setInterval(1000L, sendSensor);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
   sensors.begin();
}
int sensor=0;
void sendTemps()
{
sensor=analogRead(A0);


Serial.println(sensor);

Blynk.virtualWrite(V2,sensor);
delay(1000);
}
void loop()
{
  Blynk.run(); 
  timer.run(); 
  sendTemps();
  sensorState = digitalRead(sensorPin);
Serial.println(sensorState);


}
