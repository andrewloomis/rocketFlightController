#ifndef LED_H
#define LED_H

#include <inttypes.h>

class LED
{
public:
    LED();
    void on();
    void off();
    void error();
    void blinkFast();
    void quickBlink();

private:
    const uint8_t pin = 16;
};

#endif