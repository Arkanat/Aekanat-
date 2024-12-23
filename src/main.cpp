#include <Arduino.h>

// Pin Definitions
const int potentiometerPins[] = {36, 39, 12, 13};    // Potentiometer pins (Analog Input)
const int switchPins[] = {15, 2, 34, 35, 33, 32};    // Switch pins (Digital Input)
const int ledPins[] = {23, 19, 18, 5, 17, 16, 4, 0}; // LED pins (Digital Output)

// Variables
int ledBrightness[4] = {0, 0, 0, 0};         // Brightness of each LED group
bool ledState[4] = {true, true, true, true}; // ON/OFF state of each LED group
bool chasingMode = false;

void controlLEDBrightness()
{
  for (int i = 0; i < 4; i++)
  {
    if (ledState[i])
    {
      // Read potentiometer value and map to brightness
      ledBrightness[i] = map(analogRead(potentiometerPins[i]), 0, 4095, 0, 255);
    }
    else
    {
      ledBrightness[i] = 0; // Turn off if group is OFF
    }

    // Update LEDs in the group
    analogWrite(ledPins[i * 2], ledBrightness[i]);
    analogWrite(ledPins[i * 2 + 1], ledBrightness[i]);
  }
}

void runChasingMode()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      analogWrite(ledPins[j], (i == j) ? 255 : 0); // Only one LED is ON at a time
    }
    delay(200); // Speed of chasing effect
  }
}
void setup()
{
  Serial.begin(115200);
  // Initialize potentiometers as input
  for (int i = 0; i < 4; i++)
  {
    pinMode(potentiometerPins[i], INPUT);
  }

  // Initialize switches as input
  for (int i = 0; i < 6; i++)
  {
    pinMode(switchPins[i], INPUT_PULLUP);
  }

  // Initialize LEDs as output
  for (int i = 0; i < 8; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    analogWrite(ledPins[i], 0); // Start with all LEDs off
  }
}

void loop()
{
  // // Read switch states
  for (int i = 0; i < 4; i++) {
      if (digitalRead(switchPins[i]) == LOW) { // Switch pressed
          ledState[i] = !ledState[i]; // Toggle LED group state
          delay(200); // Debounce delay
          Serial.print("Sw Press: ");
          Serial.println(switchPins[i]);
      }
  }

  if (digitalRead(switchPins[4]) == LOW)
  { // Switch 5: Toggle chasing mode
    chasingMode = !chasingMode;
    delay(200); // Debounce delay
  }

  if (digitalRead(switchPins[5]) == LOW)
  { // Switch 6: Reset all LEDs
    chasingMode = false;
    for (int i = 0; i < 4; i++)
    {
      ledState[i] = false;
      ledBrightness[i] = 0;
    }
    for (int i = 0; i < 8; i++)
    {
      analogWrite(ledPins[i], 0);
    }
    delay(200); // Debounce delay
  }

  chasingMode ? runChasingMode() : controlLEDBrightness();
  delay(10);
}
