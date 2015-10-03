#include "ButtonGroup.h"

ButtonGroup::ButtonGroup(ButtonGroupCallback callback, void *data, long debounceDelay) : activePins(0), lastStates(0), curStates(0), lastDebounceTime(0)
{
    this->callback = callback;
    this->debounceDelay = debounceDelay;
    callbackData = data;
}
     
ButtonGroup::~ButtonGroup()
{
}

void ButtonGroup::registerPin(byte digitalPin, byte initState)
{
    bitWrite(lastStates, digitalPin, initState);
    bitWrite(curStates, digitalPin, initState);
    bitSet(activePins, digitalPin);
}

void ButtonGroup::unregisterPin(byte digitalPin)
{
    bitClear(activePins, digitalPin);
}

void ButtonGroup::readAllPins()
{
    for (int currentPin = 0; currentPin < MAX_PINS; currentPin++)
    {
        if (bitRead(activePins, currentPin))
        {
            readPin(currentPin);
        }
    }
}
    
void ButtonGroup::readPin(byte digitalPin)
{
    // Read the state of the switch into a local variable.
    int state = digitalRead(digitalPin);

    // Check to see if the pin's state has changed
    // (i.e. the input went from LOW to HIGH), and you've waited
    // long enough since the last state change to ignore any noise.

    // If the switch changed, due to noise or pressing reset the
    // debouncing timer.
    if (state != bitRead(lastStates, digitalPin))
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        // Whatever the state is at, it's been there for longer
        // than the debounce delay, so take it as the intended state
        // and notify the caller.
        int curState = bitRead(curStates, digitalPin);
        if (state != curState)
        {
            callback(digitalPin, state, curState, callbackData);
            bitWrite(curStates, digitalPin, state);
        }
    }

    // Save the state.  Next time through the loop, it'll be the
    // in lastState.
    bitWrite(lastStates, digitalPin, state);
}
