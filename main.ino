#include "barometer.h"
#include "i2c.h"
#include "coilcontroller.h"

void setup()
{

}

void loop()
{
    I2C i2c;
    Barometer baro(i2c);
    CoilController coil;
    while (1)
    {
        coil.coilPulse(baro.getAltitude());
    }
}