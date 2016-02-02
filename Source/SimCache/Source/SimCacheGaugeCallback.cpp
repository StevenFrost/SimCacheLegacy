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

#include "SimCacheGaugeCallback.h"

// Enum that contains the properties 
enum SIMCACHE_VAR
{
    SIMCACHE_VAR_DISTANCE,
    SIMCACHE_VAR_NAME,
    SIMCACHE_VAR_STATUS,
};

ULONG SIMCACHEGaugeCallback::AddRef()
{
    return ++m_RefCount;
}

ULONG SIMCACHEGaugeCallback::Release()
{
    ULONG result = --m_RefCount;
    if (result < 1)
        delete this;
    return result;
}

SIMCACHEGaugeCallback::SIMCACHEGaugeCallback(UINT32 containerId)
    : m_RefCount(1),
    m_containerId(containerId),
    m_distanceToSimCache(1.0),
    m_unitsRadians(get_units_enum("radians")),
    m_unitsMeters(get_units_enum("meters")),
    m_aircraftVarLatitude(get_aircraft_var_enum("PLANE LATITUDE")),
    m_aircraftVarLongitude(get_aircraft_var_enum("PLANE LONGITUDE")),
    m_aircraftVarAltitude(get_aircraft_var_enum("PLANE ALTITUDE"))
{ }

IGaugeCCallback* SIMCACHEGaugeCallback::QueryInterface(PCSTRINGZ pszInterface)
{
    return NULL;
}

//
// The Update functions is called on a 18Hz cycle
//
void SIMCACHEGaugeCallback::Update()
{
    FLOAT64 currentLat = aircraft_varget(m_aircraftVarLatitude, m_unitsRadians, 0);
    FLOAT64 currentLon = aircraft_varget(m_aircraftVarLongitude, m_unitsRadians, 0);
    FLOAT64 currentAlt = aircraft_varget(m_aircraftVarAltitude, m_unitsMeters, 0);

    m_distanceToSimCache = SimCache::Manager::Instance().CurrentCache()->Distance(Transformations::FromEllipsoidal(currentLat, currentLon, currentAlt));
}

//
// Getting float/numeric values
//
bool SIMCACHEGaugeCallback::GetPropertyValue(SINT32 id, FLOAT64* pValue)
{
    if (!pValue)
    {
        return false;
    }

    *pValue = 1.0;      // Start with a reasonable default
    SIMCACHE_VAR eSIMCACHEVar = (SIMCACHE_VAR)id;

    switch (eSIMCACHEVar)
    {
    case SIMCACHE_VAR_DISTANCE:
        *pValue = getSimCacheDistance();
        break;
    default:
        return false;
    }
    return true;
}

//
// Getting string property values
//
bool SIMCACHEGaugeCallback::GetPropertyValue(SINT32 id, PCSTRINGZ* pszValue)
{
    if (!pszValue)
    {
        return false;
    }

    *pszValue = "null";     // Return a reasonable default 
    SIMCACHE_VAR eSIMCACHEVar = (SIMCACHE_VAR)id;

    switch (eSIMCACHEVar)
    {
    case SIMCACHE_VAR_NAME:
        *pszValue = getSimCacheName();
        break;
    case SIMCACHE_VAR_STATUS:
        *pszValue = getSimCacheStatus();
        break;
    default:
        return false;
    }
    return true;
}

//
// Setting float/numeric values
//
bool SIMCACHEGaugeCallback::SetPropertyValue(SINT32 id, FLOAT64 value)
{
    return true;
}

//
// Setting string values
//
bool SIMCACHEGaugeCallback::SetPropertyValue(SINT32 id, PCSTRINGZ szValue)
{
    return false;
}

IGaugeCDrawable* SIMCACHEGaugeCallback::CreateGaugeCDrawable(SINT32 id, const IGaugeCDrawableCreateParameters* pParameters)
{
    return NULL;
}