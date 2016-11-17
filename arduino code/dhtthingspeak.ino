#include "DHT.h"
#include <ESP8266WiFi.h>

String APIkey="FBCLIH8H296QAEJ1";
const char* ssid="KARMAN SINGH";/*"HARLEEN KAUR";*/
const char* pass="parvinder";/*"KARMAN2712";*/
const char* server="api.thingspeak.com";
#define DHTPin 13
DHT dht(DHTPin,DHT11);
WiFiClient client;

void setup() {
Serial.begin(115200);
delay(100);
dht.begin();
WiFi.begin(ssid,pass);
//delay(200);
if(WiFi.status()!=WL_CONNECTED)
{
  delay(500);
  Serial.print(".");
  }
  Serial.println("WIFI CONNECTED");

}

void loop() {

float h=dht.readHumidity();
float t=dht.readTemperature();
if(isnan(h)||isnan(t))
{
  Serial.println("FAILED TO READ FROM SENSOR");
  return;
  } 

if(client.connect(server,80))
{
  Serial.println("client connected!");
  String Poststr=APIkey;
  Poststr+="&field1=";
  Poststr+=String(t);
  Poststr+="&field2=";
  Poststr+=String(h);
  Poststr+="\r\n\r\n";

  client.print("POST /update HTTP/1.1\n");
  client.print("Host:api.thingspeak.com\n");
  client.print("Connection:close\n");
  client.print("X-THINGSPEAKAPIKEY:"+APIkey+"\n");
  client.print("Content-Type:application/x-www-form-urlencoded\n");
  client.print("Content-Length:");
  client.print(Poststr.length());
  client.print("\n\n");
  client.print(Poststr);
  Serial.print("TEMPERATURE:");
  Serial.print(t);
  Serial.print("*C  HUMIDITY:");
  Serial.print(h);
  Serial.print("SEND TO THINGSPEAK");
}
client.stop();
//thingspeak needs min 15s to print data
delay(20000);
  
  
  }







