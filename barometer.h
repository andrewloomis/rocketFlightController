#ifndef BAROMETER_H
#define BAROMETER_H

#include "i2c.h"
#include "units.h"

class Barometer
{
public:
    Barometer(I2C& i2c);
    Centimeters getAltitude();
    Pascals getPressure();
    Celcius getTemp();

private:
    I2C& i2c;
    const uint8_t addr = 0x60;
    bool activated = false;

    void setOverSamplingRatio();
    void setActive();
    void setSleep();
    bool isDataReady();
    void initiateSample();
};

#endif