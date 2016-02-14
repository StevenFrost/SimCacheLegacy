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

#include <Windows.h>

#include <CacheManager/Cache.h>
#include <SimConnect.h>

namespace SimCache
{

//-----------------------------------------------------------------------------

class CachePositionAdapter : public SIMCONNECT_DATA_INITPOSITION
{
public:
    CachePositionAdapter(CachePosition const& cachePosition)
    {
        Latitude = cachePosition.Latitude;
        Longitude = cachePosition.Longitude;
        Altitude = cachePosition.Altitude;
        Pitch = cachePosition.Pitch;
        Bank = cachePosition.Bank;
        Heading = cachePosition.Heading;
        OnGround = 0UL;
        Airspeed = 0UL;
    }
};

//-----------------------------------------------------------------------------

} // namespace SimCache
