//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define S0 15
#define S1 2
#define S2 4
#define S3 5
#define sensorOut 18
int frequency = 0;


// Define Wifi SSID and PASS
const char* ssid = "Baška";
const char* pass = "noveheslo";
WiFiClient wifi;

// variable
int poc=0;


// setup - vykonava sa len raz pri sputeni programu
// pokusi sa pripojit k wifi
void setup()
{
  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
     
    // Setting frequency-scaling to 20%
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);
  
  WiFi.begin(ssid, pass);
  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay (1000);
    Serial.print(".");
  }

  Serial.println("Connected");
}


// vykonava sa dookola
void loop()
{
  int r, g, b, t;
// Váš kód ...
// Setting red filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    // Printing the value on the serial monitor
    Serial.print("R= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    r = frequency;
    Serial.print(" ");
    delay(100);
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    g = frequency;
    // Printing the value on the serial monitor
    Serial.print("G= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print(" ");
    delay(100);
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    // Printing the value on the serial monitor
    b = frequency;
    Serial.print("B= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.println(" ");
    delay(100);

    t = 0;
// pomocne premenne
  poc++;
  String hodnota1=String(poc);
  String hodnota2="22";
  String payload="";

  String server_name = "https://skittlessorting.azurewebsites.net/index.php?"; // nazov vasho webu a web stranky, ktoru chcete nacitat
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;
    
    server_name += "r="; // nazov premennej na webe
    
    server_name += String(r); // hodnota premmenej
    server_name += "&g="; // nazov premennej na webe
    server_name += String(g); // hodnota premennej
    server_name += "&b="; // nazov premennej na webe
    server_name += String(b); // hodnota premennej
    server_name += "&t="; // nazov premennej na webe
    server_name += String(t); // hodnota premennej
    http.begin(server_name.c_str());
    int httpCode = http.GET(); // http code

    if (httpCode>0) 
    {
      payload= http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpCode); // vypisanie http code do Serial monitoru (200 - OK)
      Serial.println(payload); // vypisanie celej html stranky, ktora sa na tejto url nachadza (zobrazene v serial monitore)

      int hodnota3 = (payload[26]); // nacitanie 2. znaku z html (>)
      Serial.println(hodnota3); // vypisanie ASCII (62) hodnoty znaku >, ktory bol nacitany v payloade
      delay(2000); // 2 sekundy 
    }
    http.end();
  }  

  // NACITANIE DAT Z WEBU
  if (WiFi.status() == WL_CONNECTED) // ak je ESP pripojene k wifi
  {
    HTTPClient http; // vytvorenie HTTP clienta
    //String server_name = "https://skittlessorting.azurewebsites.net/index.php?"; // nazov vasho webu a web stranky, ktoru chcete nacitat
    http.begin(server_name.c_str());
    int httpCode = http.GET(); // http code

    if (httpCode>0) 
      payload= http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpCode); // vypisanie http code do Serial monitoru (200 - OK)
      Serial.println(payload); // vypisanie celej html stranky, ktora sa na tejto url nachadza (zobrazene v serial monitore)

    http.end();
  }

  int hodnota3 = (payload[2]); // nacitanie 2. znaku z html (>)
  Serial.println(hodnota3); // vypisanie ASCII (62) hodnoty znaku >, ktory bol nacitany v payloade
  delay(2000); // 2 sekundy 

  // ZAPIS DAT NA WEB
  
  
}
