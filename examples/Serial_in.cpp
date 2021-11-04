#include <Arduino.h>

#define LED 2

void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
}

void loop() {
    char com = Serial.read();
    Serial.print("Recv Charecter: ");
    Serial.println(com);
    if(com == 'o'){
        digitalWrite(LED,!digitalRead(LED));
    }
}