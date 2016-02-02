/**********************************************************************************
*                                                                                *
* Copyright (c) 2016 Steven Frost, Orion Lyau. All rights reserved.              *
*                                                                                *
* This source is subject to the MIT License.                                     *
* See http://opensource.org/licenses/MIT                                         *
*                                                                                *
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,    *
* EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED          *
* WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.         *
*                                                                                *
**********************************************************************************/

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