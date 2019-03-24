// #include "barometer.h"
// #include "i2c.h"
// #include "coilcontroller.h"
// #include "led.h"
// #include "eeprom.h"
// #include "units.h"
// #include <Wire.h>

// void setup()
// {
//     Serial.begin(115200);
// }

// void loop()
// {
//     I2C i2c;
//     LED led;
//     EEPROM eeprom(true, i2c, led);
//     Barometer baro(i2c);
//     led.quickBlink();

//     float buffer[20];
//     baro.waitForLaunch(buffer, 20);
//     led.on();
//     uint16_t eepromBuffer[20];
//     for (uint8_t i = 0; i < 20; i++)
//     {
//         eepromBuffer[i] = buffer[i] > 0 ? (uint16_t)round(buffer[i]) : 0;
//     }
//     eeprom.writeData(eepromBuffer, 20);

//     while (1)
//     {
//         Meters altitude = baro.getAltitude();
//         uint16_t eepromAltitude = altitude > 0 ? (uint16_t)round(altitude) : 0;
//         eeprom.writeData(eepromAltitude);
//         if (eeprom.isFull())
//         {
//             led.blinkFast();
//         }
//         delay(baro.minInterval());
//     }
// }