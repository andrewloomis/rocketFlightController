#ifndef EEPROM_H
#define EEPROM_H

#include "i2c.h"
#include "led.h"

class EEPROM
{
public:
    EEPROM(bool startNewPartition, I2C& i2c, LED& led);
    void writeData(uint8_t* data, uint8_t numOfBytes);
    void writeData(uint16_t* data, uint8_t numOfBytes);
    void writeData(uint16_t data);
    uint8_t readDataByte(uint16_t address);
    void writeFirstPartitionToSerial();
    void writeSecondPartitionToSerial();
    bool isFull() const { return full; }
    void erase();
    
private:
    I2C& i2c;
    LED& led;
    const uint8_t i2c_address = 0x50;
    uint16_t addressPtr = 0;
    const uint16_t firstFlightStart = 0;
    const uint16_t secondFlightStart = 4096;
    bool full = false;
    enum Partition
    {
        First,
        Second
    } workingPartition;

    uint8_t readMemoryByte(uint16_t address);
    void readMemoryBytes(uint16_t startAddress, uint8_t* buffer, uint8_t length);
    bool willBeFull(uint8_t additionalBytes);
    void endRecording();
};

#endif