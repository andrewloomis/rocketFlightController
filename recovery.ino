#include "eeprom.h"
#include "i2c.h"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.println("Type 'r' to receive data");
    bool readyForData = false;
    while (!readyForData)
    {
        if (Serial.read() == 'r') readyForData = true;
    }

    I2C i2c;
    LED led;
    EEPROM eeprom(false, i2c, led);
    
    Serial.println(eeprom.readDataByte(2), HEX);
    Serial.println(eeprom.readDataByte(3), HEX);
    Serial.println("Type:\n'1' to receive p1\n'2' to receive p2\n'm' to read specific memory\n'd' to erase");
    while (Serial.available() == 0);
    char resp = Serial.read();
    // Serial.print("resp: ");
    // Serial.println(resp == 'd');
    switch (resp)
    {
    case 'd':
        Serial.println("here");
        eeprom.erase();
        break;
    case '1':
        eeprom.writeFirstPartitionToSerial();
        break;
    case '2':
        eeprom.writeSecondPartitionToSerial();
        break;
    case 'm':
        // Serial.println("Address: ");
        // while (Serial.available() == 0);
        // String response = Serial.readStringUntil('\n');
        uint16_t address = 4096;
        Serial.print("Data at ");
        // Serial.print(response);
        Serial.print(" (");
        Serial.print(address, HEX);
        Serial.print("): ");
        uint8_t data = eeprom.readDataByte(address);
        Serial.println(data, HEX);
        break;
    
    default:
        break;
    }
    Serial.println("done");
}