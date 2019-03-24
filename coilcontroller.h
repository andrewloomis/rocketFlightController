#ifndef COILCONTROLLER_H
#define COILCONTROLLER_H

#include "units.h"

class CoilController
{
public:
    CoilController();
    void startPulse(Meters altitude);
    void finishPulse();

private:
    unsigned int risingEdgeTime = 0;
};

#endif