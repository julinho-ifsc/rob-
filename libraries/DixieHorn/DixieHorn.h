#ifndef DixieHorn_h
#define DixieHorn_h

#include <Arduino.h>

class DixieHorn {
private:
    int _pin;
    int _time[12];
    int _melody[12];
public:
    DixieHorn(int pin);
    void play();
};

#endif
