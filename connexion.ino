#include <ESP8266WiFi.h>

//definition du serveur 
const char* ssid = "Kamelia";
const char* password = "kamy";

int ledPin = 13;

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 delay(10);
 pinMode(ledPin,OUTPUT);
 digitalWrite(ledPin,LOW);

 //Wifi connection
 Serial.print("connecting to : ");
 Serial.print(ssid);
 WiFi.begin(ssid,password);
 while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
 }
 Serial.println("");
 Serial.println("wifi connecté");

 //Starting server
 server.begin();
 Serial.println("Server Started");

 //print ip adress
 Serial.print("URL de connection : http://"& WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  delay(100);
}
