#include "coilcontroller.h"
#include <Arduino.h>

CoilController::CoilController()
{
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
}

void CoilController::coilPulse(Centimeters altitude)
{
    risingEdgeTime = micros();

}