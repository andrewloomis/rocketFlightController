#include "led.h"
#include <Arduino.h>

LED::LED()
{
    pinMode(pin, OUTPUT);
}

void LED::on()
{
    digitalWrite(pin, HIGH);
}

void LED::off()
{
    digitalWrite(pin, LOW);
}

void LED::error()
{
    while (1)
    {
        on();
        delay(1000);
        off();
        delay(1000);
    }
}

void LED::blinkFast()
{
    while (1)
    {
        on();
        delay(200);
        off();
        delay(200);
    }
}

void LED::quickBlink()
{
    for(uint8_t i = 0; i < 4; i++)
    {
        on();
        delay(200);
        off();
        delay(100);
    }
}