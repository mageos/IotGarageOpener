#ifndef Scheduler_h
#define Scheduler_h

class Runable
{    
public:
    virtual void run() = 0;

};

class Scheduler
{
public:
    Scheduler();

    void add(const Runable& schedule);

    void run();
};

#endif