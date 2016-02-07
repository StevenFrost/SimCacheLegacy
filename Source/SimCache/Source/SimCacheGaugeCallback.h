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

#include "CacheManager.h"

namespace SimCache
{

//-----------------------------------------------------------------------------

class SimCacheGaugeCallback : public IGaugeCCallback
{
public:
    SimCacheGaugeCallback(UINT32 containerId);

    ULONG AddRef();
    ULONG Release();

    IGaugeCCallback* QueryInterface(PCSTRINGZ object) { return nullptr; }
    void Update(); // Called on a 18Hz cycle

    bool GetPropertyValue(SINT32 id, FLOAT64* value);
    bool GetPropertyValue(SINT32 id, PCSTRINGZ* value);
    bool SetPropertyValue(SINT32 id, FLOAT64 value);
    bool SetPropertyValue(SINT32 id, PCSTRINGZ value);

    IGaugeCDrawable* CreateGaugeCDrawable(SINT32 id, const IGaugeCDrawableCreateParameters* parameters);

    double GetSimCacheDistance() const;
    const char* GetSimCacheName() const;
    const char* GetSimCacheHint() const;
    const char* GetSimCacheStatus() const;

    double GetSimCacheIndex() const;
    void SetSimCacheIndex(double value);

private:
    ULONG m_refCount;
    UINT32 m_containerId;

    double m_distanceToSimCache;
    double m_simCacheIndex;

    ENUM m_unitsRadians;
    ENUM m_unitsMeters;
    ENUM m_aircraftVarLatitude;
    ENUM m_aircraftVarLongitude;
    ENUM m_aircraftVarAltitude;
};

//-----------------------------------------------------------------------------

} // namespace SimCache
