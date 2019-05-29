#include "Led.h"

Led::Led(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void Led::on()
{
    _state = true;
    updateState();
}

void Led::off()
{
    _state = false;
    updateState();
}

void Led::toggle()
{
    _state = !_state;
    updateState();
}

void Led::updateState()
{
    uint8_t currentState = _state ? HIGH : LOW;
    digitalWrite(_pin, currentState);
}

void Led::blink(int d, int count)
{
    _currentDelay = d;
    _remaining = count;
    _blinkState = !_state;

    digitalWrite(_pin, _blinkState ? HIGH : LOW);

    _nextChange = millis() + _currentDelay;
}

void Led::run()
{
    if (_remaining > 0)
    {
        long m = millis();
        if (m >= _nextChange)
        {
            uint8_t value = _blinkState ? HIGH : LOW;
            digitalWrite(_pin, value);
            _blinkState = !_blinkState;
            _nextChange += _currentDelay;
            _remaining--;
        }

        if (_remaining <= 0)
        {
            updateState();
        }
    }
    
}