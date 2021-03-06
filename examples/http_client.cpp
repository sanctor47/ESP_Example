#include <Arduino.h>
#include <esp8266wifi.h>
#include <esp8266httpclient.h>

const char* ssid = "EME_SectorB5 Emergency";
const char* password = "EME_SectorB5";

void setup () {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
 Serial.println("Connected ....");
}

void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://jsonplaceholder.typicode.com/posts/99");  //Specify request destination
    int httpCode = http.GET();
    
    if (httpCode > 0) { //Check the returning code
 
      String data = http.getString();   //Get the request response payload
      Serial.println(data);             //Print the response payload
 
    }
    http.end();   //Close connection
 
  }
 
  delay(30000);    //Send a request every 30 seconds
}