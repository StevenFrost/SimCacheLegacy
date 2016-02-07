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

#include <gauges.h>

#include "AircraftCallback.h"
#include "SimCacheGaugeCallback.h"

namespace SimCache
{

//-----------------------------------------------------------------------------

class SimCacheAircraftCallback : public AircraftCallback
{
public:
    SimCacheAircraftCallback(UINT32 containerID) :
        AircraftCallback(containerID)
    {}

    IGaugeCCallback* CreateGaugeCCallback()
    {
        return new SimCacheGaugeCallback(GetContainerId());
    }
};

//-----------------------------------------------------------------------------

} // namespace SimCache
