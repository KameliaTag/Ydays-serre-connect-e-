#include <ESP8266WiFi.h>
#include <Arduino.h>

//  réseau
const char *ssid     = "Kamelia";
const char *password = "kamy";

// Server 
WiFiServer server(80);

#include <dht.h>
dht DHT;
// PIN humidité et temperature
#define DHT11_PIN D2
String messageDHT11;

// PIN lumière 
int pinDigitallumiere = D0;
int valueLum; 
String etatLum;
String messageLum;

void setup() {
  Serial.begin(9600);
  Serial.println();

  // Wi-Fi
  Serial.print("Connexion à ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Adresse IP 
  Serial.print("Connecté, adresse IP:");
  Serial.println(WiFi.localIP());

  // Démarrage du server
  server.begin();
 
  Serial.println("Initialisation DHT11");
  Serial.println("Initialisation lumiere");
  pinMode(pinDigitallumiere, INPUT);
}

void loop() {
  WiFiClient client = server.available();
 
  //  si pas le bon  client
  if(!client) {
    return;
  }
    //  DHT11
    int chk = DHT.read11(DHT11_PIN);
    while (DHT.temperature == 0 or DHT.humidity == 0) {
      int chk = DHT.read11(DHT11_PIN);
    }    
    
    // lumiere
    valueLum = digitalRead(pinDigitallumiere);
    if (valueLum == 0) {
      etatLum = "allumee";
      messageLum = "Eteindre la lumiere";
    } else {
      etatLum = "Lum-eteinte";
      messageLum = "Allumer la lumiere";
    }
  

  // Affichage
  client.println("HTTP  ");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>"); 
  client.println("<h1> Serre connecté  :</h1>");
  client.print("Temperature: ");
  client.println(DHT.temperature);
  client.print("Humidite: ");
  client.println(DHT.humidity);
  Serial.println("");
}
