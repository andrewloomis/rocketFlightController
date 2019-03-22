#include "barometer.h"

Barometer::Barometer(I2C& i2c)
    : i2c(i2c)
{
    setOverSamplingRatio();
    initiateSample();
}

void Barometer::setOverSamplingRatio()
{
    i2c.writeRegByte(addr, 0x26, 0b10010000);
}

void Barometer::setActive()
{
    activated = true;
    uint8_t data = i2c.readRegByte(addr, 0x26) + 1;
    i2c.writeRegByte(addr, 0x26, data);
}

bool Barometer::isDataReady()
{
    return (i2c.readRegByte(addr, 0x06) & 0x06);
}

void Barometer::initiateSample()
{
    uint8_t currentSetting = i2c.readRegByte(addr, 0x26);
    uint8_t clearOST = currentSetting & ~(1 << 1);
    i2c.writeRegByte(addr, 0x26, clearOST);
    uint8_t setOST = currentSetting | (1 << 1);
    i2c.writeRegByte(addr, 0x26, setOST);
}

Centimeters Barometer::getAltitude()
{
    if (!activated) setActive();
    uint8_t data[3];
    i2c.readRegBytes(addr, 0x01, data, 3);

    Centimeters altitude = ((data[0] << 8) | data[1]) * 100 + 
        ((data[0] >> 4) * (100/16));
    initiateSample();

    return altitude;
}
