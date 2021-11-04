#include <Arduino.h>
#include <ESP8266WiFi.h>

/*ADD YOUR PASSWORD BELOW*/
const char *ssid = "SECRET_SSID";
const char *password = "SECRET_PASS";

WiFiClient espClient;

void setup(){

    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
}

void loop(){
    
}