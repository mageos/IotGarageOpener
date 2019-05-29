#ifndef LED_h
#define LED_h

#include "Scheduler.h"

class Led : public Runable
{
    public:
        Led(uint8_t pin);

        void on();
        void off();
        void toggle();
        void blink(int delay, int count);

        void run();

    private:
        long _nextChange = 0;
        int _currentDelay = 0;
        int _remaining = 0;
        uint8_t _pin;
        bool _state;     
        bool _blinkState = false;

        void updateState();
};

#endif