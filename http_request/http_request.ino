//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "DHT.h"
#include <Servo_ESP32.h>

#define DHT11PIN 12
#define S0 15
#define S1 2
#define S2 4
#define S3 5
#define sensorOut 18
DHT dht(DHT11PIN, DHT11);

static const int topServoPin = 13;
Servo_ESP32 topServo;

static const int bottomServoPin = 14;
Servo_ESP32 bottomServo;


const char* ssid = "Baška";
const char* pass = "noveheslo";
WiFiClient wifi;

void setup()
{
  Serial.begin(9600);
  dht.begin();

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
     
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);
  
  topServo.attach(topServoPin); 
  bottomServo.attach(bottomServoPin);

  WiFi.begin(ssid, pass);
  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay (1000);
    Serial.print(".");
  }

  Serial.println("Connected");
}

void loop()
{
  float temp = getTemperature();
  int red = getRed();
  int green = getGreen();
  int blue = getBlue();
  printRGBtoSerial(red, green, blue, temp);
  
  topServo.write(180); // initial position
  delay(500);

  for(int i = 180; i > 130; i--){
     topServo.write(i);
     delay(2);
  }
  delay(500);

  topServo.write(130);
  delay(500);
  
  

  //String hodnota1=String(poc);
  //String hodnota2="22";
  String payload="";

  
// ZAPIS DAT NA WEB
  String server_name = "https://skittlessorting.azurewebsites.net/index.php?"; 
  
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;
    
    server_name += "R="; 
    server_name += String(r); 
    server_name += "&G="; 
    server_name += String(g); 
    server_name += "&B=";
    server_name += String(b); 
    server_name += "&T="; 
    server_name += String(t); 
    http.begin(server_name.c_str());
    int httpCode = http.GET(); 

    if (httpCode>0) 
    {
      payload= http.getString();
      //Serial.print("HTTP Response code: ");
      //Serial.println(httpCode); // vypisanie http code do Serial monitoru (200 - OK)
      //Serial.println(payload); // vypisanie celej html stranky, ktora sa na tejto url nachadza (zobrazene v serial monitore)

      //int hodnota3 = (payload[26]); // nacitanie 2. znaku z html (>)
      //Serial.println(hodnota3); // vypisanie ASCII (62) hodnoty znaku >, ktory bol nacitany v payloade
      //delay(2000); // 2 sekundy 
    }
    http.end();
  }  

  // NACITANIE DAT Z WEBU
  if (WiFi.status() == WL_CONNECTED) // ak je ESP pripojene k wifi
  {
    HTTPClient http; // vytvorenie HTTP clienta
    
    http.begin(server_name.c_str());
    int httpCode = http.GET(); // http code

    if (httpCode>0) 
      payload= http.getString();
      //Serial.print("HTTP Response code: ");
      //Serial.println(httpCode); // vypisanie http code do Serial monitoru (200 - OK)
      //Serial.println(payload); // vypisanie celej html stranky, ktora sa na tejto url nachadza (zobrazene v serial monitore)

    http.end();
  }

  int hodnota3 = (payload[2]); // nacitanie 2. znaku z html (>)
  Serial.println(hodnota3); // vypisanie ASCII (62) hodnoty znaku >, ktory bol nacitany v payloade
  delay(2000); // 2 sekundy 


  for(int i = 130; i > 90; i--){
     topServo.write(i);
     delay(2);
  }
  delay(500);
  delay(500);
}

int getAngleFromServer(int red, int green, int blue, int temperature){
  
  return 0;
}


int getRed(){
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  int red = pulseIn(sensorOut, LOW);
  return red;
}
int getBlue(){
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  int blue = pulseIn(sensorOut, LOW);
  return blue;
}
int getGreen(){
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  int green = pulseIn(sensorOut, LOW);
  return green;
}
float getTemperature(){
  return dht.readTemperature();
}

void printRGBtoSerial(int red, int green, int blue, float temp){
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" ");
  Serial.print("R= ");//printing name
  Serial.print(red);//printing RED color frequency
  Serial.print(" ");
  Serial.print("G= ");//printing name
  Serial.print(green);//printing RED color frequency
  Serial.print(" ");
  Serial.print("B= ");//printing name
  Serial.print(blue);//printing RED color frequency
  Serial.println(" ");
  delay(1000);
}
