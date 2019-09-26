#include "barometer.h"
#include "i2c.h"
#include "coilcontroller.h"
#include "led.h"
#include "eeprom.h"
#include "units.h"
#include <Wire.h>

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    I2C i2c;
    LED led;
    EEPROM eeprom(true, i2c, led);
    Barometer baro(i2c);
    CoilController coil;
    led.quickBlink();

    float buffer[20];
    baro.waitForLaunch(buffer, 20);
    led.on();
    uint16_t eepromBuffer[20];
    for (uint8_t i = 0; i < 20; i++)
    {
        eepromBuffer[i] = buffer[i] > 0 ? (uint16_t)round(buffer[i]) : 0;
    }
    eeprom.writeData(eepromBuffer, sizeof(eepromBuffer));

    while (1)
    {
        Meters altitude = baro.getAltitude();
        coil.startPulse(altitude);
        uint16_t roundedAltitude = altitude > 0 ? (uint16_t)round(altitude) : 0;
        eeprom.writeData(roundedAltitude);
        if (eeprom.isFull())
        {
            led.blinkFast();
        }
        coil.finishPulse(baro.minInterval());
        // delay(baro.minInterval());
    }
}