#ifndef Button_h
#define Button_h

#include "Scheduler.h"

typedef void (*BUTTON_CLICK_HANDLER)();

class Button : public Runable
{
    public:
        Button(uint8_t pin, BUTTON_CLICK_HANDLER);
        void poll();
        void run();

    private:
        BUTTON_CLICK_HANDLER _handler;
        unsigned long _lastPoll;
        uint8_t _pin;
        bool _state;
};

#endif