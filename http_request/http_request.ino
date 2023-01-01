//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

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
const String url = "https://skittlessorting.azurewebsites.net/"; 

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
  
  int angle = getAngleFromServer(red, green, blue, temp);
  Serial.println("Angle");
  Serial.println(angle);

  // TODO: nastavenie uhlu pre servo

  delay(1000);

  for(int i = 130; i > 90; i--){
     topServo.write(i);
     delay(2);
  }
  delay(1000);
}

int getAngleFromServer(int red, int green, int blue, int temperature){
  
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;

    http.begin(url);
    http.addHeader("Content-Type", "Content-Type: application/json"); 
    
    StaticJsonDocument<64> json;

    json["r"] = red;
    json["g"] = green;
    json["b"] = blue;
    json["t"] = temperature;

    String requestBody;
    serializeJson(json, requestBody);

    int httpResponseCode = http.POST(requestBody);

    if(httpResponseCode > 0) {
      String response =  http.getString();
      return response.toInt();
    }
    else{
      Serial.printf("Error with sending POST");
    }
  }  
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
  float temperature = dht.readTemperature();
  return isnan(temperature) ? 0.0 : dht.readTemperature();
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
