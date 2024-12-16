#include <Arduino.h>

int potPin = 36;
int ledPin = 23;

void setup(){
  ledcAttachPin(ledPin, 0);
  ledcSetup(0, 5000, 8);
}

void loop(){
  int potVaiue = analogRead(potPin);
  int dutyCycle = map(potValue, 0, 4095, 0, 255);
  ledcWrite(0, dutyCycle);
  delay(10);
}