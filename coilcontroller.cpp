#include "coilcontroller.h"
#include <Arduino.h>

CoilController::CoilController()
{
}

void CoilController::startPulse(Meters altitude)
{
    risingEdgeTime = micros();
    allOn();
    
}

void CoilController::finishPulse(Milliseconds minInterval)
{

}

void CoilController::allOn()
{
    coils[0].on();
    coils[1].on();
    coils[2].on();
}

void CoilController::allOff()
{
    coils[0].off();
    coils[1].off();
    coils[2].off();
}