#include "barometer.h"

Barometer::Barometer(I2C& i2c)
    : i2c(i2c)
{
    uint8_t whoami = i2c.readRegByte(addr, 0x0C);
    Serial.print("Baro ID: ");
    Serial.println(whoami, HEX);
    setOverSamplingRatio();
    i2c.writeRegByte(addr, 0x13, 0x07);

    initiateSample();
    delay(minSampleInterval);

    calibrateStartingHeight();
}

void Barometer::setOverSamplingRatio()
{
    i2c.writeRegByte(addr, 0x26, 0b10100000);
}

void Barometer::calibrateStartingHeight()
{
    Meters total = 0;
    const uint8_t reps = 30;
    for (uint8_t i = 0; i < reps; i++)
    {
        total += getAltitude();
        delay(minSampleInterval);
    }
    startingHeight = total / reps;
}

void Barometer::setActive()
{
    activated = true;
    uint8_t data = i2c.readRegByte(addr, 0x26) + 1;
    i2c.writeRegByte(addr, 0x26, data);
}

bool Barometer::isDataReady()
{
    return (i2c.readRegByte(addr, 0x00) & 0x04);
}

void Barometer::initiateSample()
{
    uint8_t currentSetting = i2c.readRegByte(addr, 0x26);
    // uint8_t clearOST = currentSetting & ~(1 << 1);
    // i2c.writeRegByte(addr, 0x26, clearOST);
    uint8_t setOST = currentSetting | (1 << 1);
    i2c.writeRegByte(addr, 0x26, setOST);
}

Meters Barometer::getAltitude()
{
    // if (!activated) setActive();
    if (isDataReady())
    {
        uint8_t data[3];
        i2c.readRegBytes(addr, 0x01, data, 3);

        Meters altitude = (float)((data[0] << 8) | data[1]) + 
            ((float)(data[2] >> 4) / 16.0f);
        initiateSample();

        altitude = altitude - startingHeight;
        return altitude;
    }
    else return -1;
}

float Barometer::findRange(float* numbers, uint8_t length)
{
    float min, max, diff;
    min = numbers[0];
    max = numbers[0];
    for (uint8_t i = 1; i < length; i++)
    {
        if (numbers[i] < min) min = numbers[i];
        if (max < numbers[i]) max = numbers[i];
    }

    diff = max - min;
    return diff;
}

float Barometer::findAvg(float* numbers, uint8_t length)
{
    float total = 0;
    for (uint8_t i = 0; i < length; i++)
    {
        total += numbers[i];
    }
    return total / length;
}

void Barometer::waitForLaunch(float* output, uint8_t length)
{
    const uint8_t maxBufferSize = 20;
    if (length <= maxBufferSize)
    {
        float buffer[maxBufferSize] = {0};
        while (findRange(buffer, length) < 4.5f && findAvg(buffer, length) < 5.0f)
        {
            for (uint8_t i = 0; i < length; i++)
            {
                buffer[i] = getAltitude();
                delay(minSampleInterval);
            }
        }

        memcpy(output, buffer, length*sizeof(float));
    }
}
