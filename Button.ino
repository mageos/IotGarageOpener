#include "Button.h"

Button::Button(uint8_t pin, BUTTON_CLICK_HANDLER handler)
{
    _pin = pin;    
    _handler = handler;
    pinMode(_pin, INPUT);
}

void Button::run()
{
    poll();    
}

void Button::poll()
{
    unsigned long currentPoll = millis();
    
    if (currentPoll - _lastPoll <= 100)
    {
        return;
    }

    bool state = digitalRead(_pin) == HIGH;    

    if (state != _state)
    {        
        _state = state;
        if (_state)
        {
            _handler();            
        }                
    }

    _lastPoll = currentPoll;

    String message = "Button " + String(_pin) + " is ";    
}