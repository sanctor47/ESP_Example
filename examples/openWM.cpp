#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJSON.h>

const char *ssid = "EME_SectorB5 Emergency";
const char *password = "EME_SectorB5";

// Your Domain name with URL path or IP address with path
String openWeatherMapApiKey = "844292914c037c4d5a6cf307b01a544f";

// Replace with your country code and city
String city = "Cairo";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

String jsonBuffer;

String httpGETRequest(const char *serverName)
{
  WiFiClient client;
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(client, serverName);

  int httpResponseCode = http.GET();

  String payload = "";

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay)
  {
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&APPID=" + openWeatherMapApiKey;

      jsonBuffer = httpGETRequest(serverPath.c_str());
      // Serial.println(jsonBuffer);

      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, jsonBuffer);

      // Test if parsing succeeds.
      if (error)
      {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      // serializeJsonPretty(doc, Serial);

      double temp = doc["main"]["temp"];
      String weather = doc["weather"][0]["main"];

      Serial.println("_____________________");
      Serial.print("Current Temp: ");
      Serial.println(temp);
      Serial.println("_____________________");
       Serial.println("_____________________");
      Serial.print("Current : ");
      Serial.println(weather);
      Serial.println("_____________________");
    }
    lastTime = millis();
  }
}