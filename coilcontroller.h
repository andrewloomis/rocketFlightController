#ifndef COILCONTROLLER_H
#define COILCONTROLLER_H

#include "units.h"
#include "coil.h"

class CoilController
{
public:
    CoilController();
    void startPulse(Meters altitude);
    void finishPulse(Milliseconds minInterval);

private:
    Coil coils[3] = {Coil(3), Coil(5), Coil(6)};
    unsigned int risingEdgeTime = 0;

    void allOn();
    void allOff();
};

#endif