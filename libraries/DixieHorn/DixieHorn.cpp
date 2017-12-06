#include <DixieHorn.h>
#include <Arduino.h>

DixieHorn::DixieHorn(int pin) {
    _pin = pin;
    pinMode(pin, OUTPUT);

    _melody = {
      390, //g
      330, //e
      262, //low c
      262, //low c
      262, //low c
      294, //low d
      330, //e
      348, //f
      390, //g
      390, //g
      390, //g
      330  //e
    };

    _time = {
      16,
      16,
      8,
      8,
      16,
      16,
      16,
      16,
      8,
      8,
      8,
      8
    };
}

void DixieHorn::play() {
    int size = sizeof(_melody) / sizeof(_melody[0]);

    for (int i = 0; i < size; i++) {
        tone(_pin, _melody[i], 2980 / _time[i]);
        delay(3000 / _time[i]);
    }
}
