#ifndef COILCONTROLLER_H
#define COILCONTROLLER_H

#include "units.h"

class CoilController
{
public:
    CoilController();
    void coilPulse(Centimeters altitude);

private:
    unsigned int risingEdgeTime = 0;
};

#endif