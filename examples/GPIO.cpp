#include <Arduino.h>

#define LED 2
#define BTN 3

void setup() {
    pinMode(LED,OUTPUT);
    pinMode(BTN,INPUT);
}

void loop() {
    if(digitalRead(BTN) == HIGH){
        digitalWrite(LED,HIGH);
    }
    else{
        digitalWrite(LED,LOW);
    }
}