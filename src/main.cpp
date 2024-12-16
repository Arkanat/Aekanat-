#include <Arduino.h>

const int potPin = 36;
const int ledPins[] = {23, 19, 13, 6, 17, 16, 4, 0};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

void setup() {
  
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  Serial.begin(115200);
}

void loop() {
  int potValue = analogRead(potPin);
  float voltage = potValue * (3.3 / 4095.0);

  Serial.print("Potentiometer Voltage: ");
  Serial.println(voltage);

 
  if (voltage < 1.0) {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  } else if (voltage < 2.0) {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], (i < 3) ? HIGH : LOW);
    }
  } else if (voltage < 3.0) {
        for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], (i < 5) ? HIGH : LOW);
    }
  } else {
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
  }
  delay(100);
}