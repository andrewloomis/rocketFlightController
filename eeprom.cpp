#include "eeprom.h"

EEPROM::EEPROM(I2C& i2c)
    : i2c(i2c)
{
    const uint16_t firstFlightStart = 0;
    const uint16_t secondFlightStart = 4096;

    if (readMemoryByte(firstFlightStart) == 0xFF)
    {
        uint8_t* intro = "F001";
        addressPtr = firstFlightStart;
        i2c.writeReg16Bytes(i2c_address, addressPtr, intro, sizeof(intro));
    }
    else if (readMemoryByte(secondFlightStart) == 0xFF)
    {
        uint8_t* intro = "F002";
        addressPtr = secondFlightStart;
        i2c.writeReg16Bytes(i2c_address, addressPtr, intro, sizeof(intro));
    }
    else
    {
        uint8_t firstFlightIntro[4];
        readMemoryBytes(firstFlightStart, firstFlightIntro, sizeof(firstFlightIntro));

        uint8_t secondFlightIntro[4];
        readMemoryBytes(secondFlightStart, secondFlightIntro, sizeof(secondFlightIntro));

        if (firstFlightIntro[0] == 'F' && secondFlightIntro[0] == 'F')
        {

        }
        else
        {
            
        }
    }
    
}

uint8_t EEPROM::readMemoryByte(uint16_t address)
{
    i2c.readReg16Byte(i2c_address, address)
}