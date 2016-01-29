#pragma once

#include "gauges.h"

//
// AircraftCallback Override
//
class SIMCACHEAircraftCallback : public AircraftCallback
{
private:

public:
    SIMCACHEAircraftCallback(UINT32 ContainerID) : AircraftCallback(ContainerID)
    {}
    IGaugeCCallback* CreateGaugeCCallback()
    {
        return new SIMCACHEGaugeCallback(GetContainerId());
    }
};