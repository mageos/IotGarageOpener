#ifndef Thermometer_h
#define Thermometer_h

#include "Scheduler.h"

#define AVERAGE_COUNT 10

class Thermometer : public Runable
{
public:
    Thermometer(uint8_t pin);
    void sample();

    void run();

    float lastReadingF();
    float lastReadingC();
    float averaged();
    float averagedC();
    float averagedF();

private:    
    long _lastSample;
    uint8_t _pin;
    byte _lastReading;
    float _readings[AVERAGE_COUNT];
};

#endif