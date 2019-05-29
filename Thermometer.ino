#include "Thermometer.h"

Thermometer::Thermometer(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, INPUT);
}

void Thermometer::sample()
{
    auto m = millis();

    if (m - _lastSample < 100)
    {
        return;
    }

    _lastSample = m;

    float voltage = (analogRead(_pin) * 3.3f) / 1024;

    _lastReading++;

    if (_lastReading >= AVERAGE_COUNT)
    {
        _lastReading = 0;
    }

    _readings[_lastReading] = voltage;
}

void Thermometer::run()
{
    sample();
}

float Thermometer::lastReadingC()
{
    return (_readings[_lastReading] - 0.5f) * 100.0;
}

float Thermometer::lastReadingF()
{
    return (lastReadingC() * 1.8) + 32.0f;
}

float Thermometer::averaged()
{
    float sum = 0;
    for (int i=0; i < AVERAGE_COUNT; i++)
    {
        sum += _readings[i];
    }

    return sum / AVERAGE_COUNT;
}

float Thermometer::averagedC()
{
    return (averaged() - 0.5f) * 100;
}

float Thermometer::averagedF()
{    
    return (averagedC() * 1.8) + 32.0f;
}