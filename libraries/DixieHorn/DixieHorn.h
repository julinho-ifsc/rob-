#ifndef DixieHorn_h
#define DixieHorn_h

#include <Arduino.h>

class EngineControl {
private:
    int _pin;
    int _time[];
    int _melody[];
public:
    DixieHorn(int pin);
    void play();
};

#endif
