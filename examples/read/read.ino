#include "ButtonGroup.h"

void callback(byte pin, int newState, int oldState, void *data)
{
    char buffer[100];
    sprintf(buffer, "Pin %d changed from %s to %s", pin,
            oldState ? "HIGH" : "LOW", newState ? "HIGH" : "LOW");
    Serial.println(buffer);
}

ButtonGroup buttonGroup(callback, NULL);
const byte button2Pin = 2;
const byte button3Pin = 3;
const byte button4Pin = 4;

void setup()
{
    Serial.begin(57600);
    // Button 2 is using an external pulldown resistor.
    pinMode(button2Pin, INPUT);
    buttonGroup.registerPin(button2Pin, LOW);
    // Button 3 is using an external pullup resistor.
    pinMode(button3Pin, INPUT);
    buttonGroup.registerPin(button3Pin, HIGH);
    // Button 4 is using Arduino's internal pullup resistor.
    pinMode(button4Pin, INPUT_PULLUP);
    buttonGroup.registerPin(button4Pin, HIGH);
    Serial.println("Pin 2 is LOW");
    Serial.println("Pin 3 is HIGH");
    Serial.println("Pin 4 is HIGH");
    
}

void loop()
{
    buttonGroup.readAllPins();
}
