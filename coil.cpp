#include "coil.h"

Coil::Coil(uint8_t pin)
    : pin(pin)
{
    pinMode(pin, OUTPUT);
}

void Coil::on()
{
    digitalWrite(pin, HIGH);
}

void Coil::off()
{
    digitalWrite(pin, LOW);
}