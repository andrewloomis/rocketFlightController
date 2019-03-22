#include "i2c.h"

I2C::I2C()
{
    Wire.begin();
    Wire.setClock(400000);
}

void I2C::writeRegByte(uint8_t addr, uint8_t reg, uint8_t data)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

uint8_t I2C::readRegByte(uint8_t addr, uint8_t reg)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.requestFrom(addr, 1);
    uint8_t data = Wire.read();
    Wire.endTransmission();
    return data;
}

void I2C::readRegBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.requestFrom(addr, length);
    for (uint8_t i = 0; i < length; i++)
    {
        buffer[i] = Wire.read();
    }
    Wire.endTransmission();
    
}