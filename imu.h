#ifndef IMU_H
#define IMU_H

#include "i2c.h"

class IMU
{
public:
    IMU(I2C& i2c);
    float getAcceleration();

private:
    I2C& i2c;
    uint8_t i2c_address = 0x68;
};

#endif