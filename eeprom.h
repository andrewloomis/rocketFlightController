#ifndef EEPROM_H
#define EEPROM_H

#include "i2c.h"

class EEPROM
{
public:
    EEPROM(I2C& i2c);
    void writeData(uint8_t* data, uint8_t length);
    
private:
    I2C i2c;
    const uint8_t i2c_address = 0x50;
    uint16_t addressPtr = 0;

    uint8_t readMemoryByte(uint16_t address);
    void readMemoryBytes(uint16_t startAddress, uint8_t* buffer, uint8_t length);
};

#endif