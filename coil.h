#ifndef COIL_H
#define COIL_H

#include <Arduino.h>

class Coil
{
public:
    Coil(uint8_t pin);
    void on();
    void off();

private:
    const uint8_t pin;
};

#endif