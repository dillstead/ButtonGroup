/*
  Wrapper around public domain debouncing code that can be found here:
  http://www.arduino.cc/en/Tutorial/Debounce

  This code allows you to register a callback that is called each
  time the pin that you are reading's state changes.
 */

#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H
     
#include <Arduino.h>

#define MAX_PINS 16

typedef void (*ButtonGroupCallback)(byte digitalPin, int newState, int oldState, void *data);

class ButtonGroup
{
public:
    ButtonGroup(ButtonGroupCallback callback, void *data, long debounceDelay = 50);
    ~ButtonGroup();

    void registerPin(byte digitalPin, byte initState);
    void unregisterPin(byte digitalPin);
    void readAllPins();
    void readPin(byte digitalPin);

private:
    ButtonGroupCallback callback;
    void *callbackData;
    // Enough space for MAX_PINS pins.
    uint16_t activePins;
    uint16_t lastStates;
    uint16_t curStates;
    // Number of milliseconds to wait for the button to debounce.  Increase
    // this if the button continues to bounce.
    unsigned long debounceDelay;
    // The last time the pin was toggled.
    unsigned long lastDebounceTime;
};
     
#endif
