#include "eeprom.h"
#include <Arduino.h>

EEPROM::EEPROM(bool startNewPartition, I2C& i2c, LED& led)
    : i2c(i2c), led(led)
{
    if (startNewPartition)
    {
        const char* intro = "F01";
        i2c.writeReg16Bytes(i2c_address, firstFlightStart, (uint8_t*)intro, sizeof(intro));
        addressPtr = firstFlightStart + sizeof(intro);
        workingPartition = Partition::First;
        // if (readMemoryByte(firstFlightStart) == 0xFF)
        // {
        //     Serial.println("Using first partition");
        //     const char* intro = "F01";
        //     i2c.writeReg16Bytes(i2c_address, firstFlightStart, (uint8_t*)intro, sizeof(intro));
        //     addressPtr = firstFlightStart + sizeof(intro);
        //     workingPartition = Partition::First;
        // }
        // else if (readMemoryByte(secondFlightStart) == 0xFF)
        // {
        //     Serial.println("Using second partition");
        //     const char* intro = "F02";
        //     i2c.writeReg16Bytes(i2c_address, secondFlightStart, (uint8_t*)intro, sizeof(intro));
        //     addressPtr = secondFlightStart + sizeof(intro);
        //     workingPartition = Partition::Second;
        // }
        // else
        // {
        //     char firstFlightIntro[4];
        //     readMemoryBytes(firstFlightStart, (uint8_t*)firstFlightIntro, sizeof(firstFlightIntro));

        //     char secondFlightIntro[4];
        //     readMemoryBytes(secondFlightStart, (uint8_t*)secondFlightIntro, sizeof(secondFlightIntro));

        //     if (firstFlightIntro[0] == 'F' && secondFlightIntro[0] == 'F')
        //     {
        //         uint8_t firstNum = atoi(firstFlightIntro + 1);
        //         uint8_t secondNum = atoi(secondFlightIntro + 1);
        //         // First flight more recent
        //         if (firstNum > secondNum)
        //         {
        //             Serial.println("Using second partition");
        //             char intro[4] = {};
        //             itoa(firstNum + 1, intro + 1, 10);
        //             intro[0] = 'F';
        //             i2c.writeReg16Bytes(i2c_address, secondFlightStart, (uint8_t*)intro, sizeof(intro));
        //             addressPtr = secondFlightStart + sizeof(intro);
        //             workingPartition = Partition::Second;
        //         }
        //         // Second flight more recent
        //         else
        //         {
        //             Serial.println("Using first partition");
        //             char intro[4] = {};
        //             itoa(secondNum + 1, intro + 1, 10);
        //             intro[0] = 'F';
        //             i2c.writeReg16Bytes(i2c_address, firstFlightStart, (uint8_t*)intro, sizeof(intro));
        //             addressPtr = firstFlightStart + sizeof(intro);
        //             workingPartition = Partition::First;
        //         }
        //     }
        //     else
        //     {
        //         led.error();
        //     }
        // }
    }
}

uint8_t EEPROM::readMemoryByte(uint16_t address)
{
    i2c.readReg16Byte(i2c_address, address);
}

void EEPROM::readMemoryBytes(uint16_t startAddress, uint8_t* buffer, uint8_t length)
{
    i2c.readReg16Bytes(i2c_address, startAddress, buffer, length);
}

bool EEPROM::willBeFull(uint8_t additionalBytes)
{
    if ((workingPartition == Partition::First && (addressPtr + additionalBytes >= secondFlightStart))
        || (workingPartition == Partition::Second && (addressPtr + additionalBytes >= 8192)))
    {
        
        return true;
    }
    else return false;
}

void EEPROM::endRecording()
{
    full = true;
    const char* end = "EOF";
    uint16_t address;
    if (workingPartition == Partition::First)
    {
        if (addressPtr + sizeof(end) >= secondFlightStart)
        {
            address = secondFlightStart - 4;
        }
        else
        {
            address = addressPtr;
        }
    }
    i2c.writeReg16Bytes(i2c_address, address, (uint8_t*)end, sizeof(end));
}

void EEPROM::writeData(uint8_t* data, uint8_t numOfBytes)
{
    if (full) return;
    if (willBeFull(numOfBytes))
    {
        endRecording();
    }
    else
    {
        i2c.writeReg16Bytes(i2c_address, addressPtr, data, numOfBytes);
        addressPtr += numOfBytes;
    }
}

void EEPROM::writeData(uint16_t* data, uint8_t numOfBytes)
{
    if (full) return;
    if (willBeFull(numOfBytes))
    {
        endRecording();
    }
    else
    {
        i2c.writeReg16Words(i2c_address, addressPtr, data, numOfBytes/2);
        addressPtr += numOfBytes;
    }
}

void EEPROM::writeData(uint16_t data)
{
    writeData(&data, 2);
}

uint8_t EEPROM::readDataByte(uint16_t address)
{
    return readMemoryByte(address);
}

void EEPROM::writeFirstPartitionToSerial()
{
    Serial.print((char)readDataByte(0));
    Serial.print((char)readDataByte(1));
    Serial.print((char)readDataByte(2));
    Serial.println((char)readDataByte(3));
    for (uint16_t i = 4; i < secondFlightStart; i += 2)
    {
        Serial.println((readDataByte(i) << 8) | readDataByte(i+1));
    }
}

void EEPROM::writeSecondPartitionToSerial()
{
    Serial.print((char)readDataByte(secondFlightStart));
    Serial.print((char)readDataByte(secondFlightStart+1));
    Serial.print((char)readDataByte(secondFlightStart+2));
    Serial.println((char)readDataByte(secondFlightStart+3));
    for (uint16_t i = secondFlightStart+4; i < 8192; i += 2)
    {
        uint8_t high = readDataByte(i);
        delay(3);
        uint8_t low = readDataByte(i+1);
        delay(3);
        Serial.println((high << 8) | low);
        
    }
}

void EEPROM::erase()
{
    for (uint16_t i = 0; i < 8192; i++)
    {
        i2c.writeReg16Byte(i2c_address, i, 0xFF);
        delayMicroseconds(100);
    }
}