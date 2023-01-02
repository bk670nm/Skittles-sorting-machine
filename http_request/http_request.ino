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
#define rPin 21
#define gPin 22
#define bPin 23
#define btnPin 19

DHT dht(DHT11PIN, DHT11);

static const int topServoPin = 13;
Servo_ESP32 topServo;

static const int bottomServoPin = 14;
Servo_ESP32 bottomServo;

const char* ssid = "Baška";
const char* pass = "noveheslo";
const String url = "https://skittlessorting.azurewebsites.net/"; 

float temp = 0.0;
int red = 0;
int green = 0;
int blue = 0;
int angle = 0;

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
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
     
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
  if(!digitalRead(btnPin) && WiFi.status() == WL_CONNECTED) {
      turnOfLeds();
      topServo.write(180); 
      delay(500);
    
      for(int i = 180; i >= 130; i--){
         topServo.write(i);
         delay(2);
      }
      delay(500);
   
      temp = getTemperature();
      red = getRed();
      green = getGreen();
      blue = getBlue();
      printRGBtoSerial();
      
      angle = getAngleFromServer();
      Serial.print("Angle ");
      Serial.println(angle);
      
      colorLed(angle);
      delay(1000);
    
      bottomServo.write(angle);
      delay(500);
    
      for(int i = 130; i > 90; i--){
         topServo.write(i);
         delay(5);
      }
      delay(1000);  
  }
}

int getAngleFromServer(){
  
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;

    http.begin(url);
    http.addHeader("Content-Type", "Content-Type: application/json"); 
    StaticJsonDocument<64> json;

    json["r"] = red;
    json["g"] = green;
    json["b"] = blue;
    json["t"] = temp;

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

void colorLed(int angle){
  if(angle == 60) {
    analogWrite(rPin, 102);
    analogWrite(gPin, 0);
    analogWrite(bPin, 102);
    delay(100);
  }
  if(angle == 30){
    analogWrite(rPin, 255);
    analogWrite(gPin, 255);
    analogWrite(bPin, 0);
    delay(100);
  }
  if(angle == 90){
    analogWrite(rPin, 0);
    analogWrite(gPin, 255);
    analogWrite(bPin, 0);
    delay(100);
  }
}
void turnOfLeds(){
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
}

int getRed(){
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  return pulseIn(sensorOut, LOW);
}
int getBlue(){
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  return pulseIn(sensorOut, LOW);
}
int getGreen(){
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  return pulseIn(sensorOut, LOW);
}
float getTemperature(){
  float temperature = dht.readTemperature();
  return isnan(temperature) ? 0.0 : dht.readTemperature();
}

void printRGBtoSerial(){
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
  delay(100);
}
