#pragma once

#include "gauges.h"

#include "CacheManager.h"

//
// Class that implements IGaugeCCallback
//
class SIMCACHEGaugeCallback : public IGaugeCCallback
{
public:
    SIMCACHEGaugeCallback(UINT32 containerId);

    ULONG AddRef();
    ULONG Release();

    // ************* IGaugeCCallback Methods ***************
    IGaugeCCallback* QueryInterface(PCSTRINGZ pszInterface);
    void Update();
    bool GetPropertyValue(SINT32 id, FLOAT64* pValue);
    bool GetPropertyValue(SINT32 id, PCSTRINGZ* pszValue);
    bool SetPropertyValue(SINT32 id, FLOAT64 value);
    bool SetPropertyValue(SINT32 id, PCSTRINGZ szValue);
    IGaugeCDrawable* CreateGaugeCDrawable(SINT32 id, const IGaugeCDrawableCreateParameters* pParameters);

    double getSimCacheDistance()
    {
        return m_distanceToSimCache;
    }

    const char* getSimCacheName()
    {
        return SimCache::Manager::Instance().CurrentCache()->Name().c_str();
    }

    const char* getSimCacheStatus()
    {
        if (m_distanceToSimCache < 1852 * 2)
        {
            return "Less than 2 nm away";
        }
        else if (m_distanceToSimCache < 1852 * 5)
        {
            return "Less than 5 nm away";
        }
        else if (m_distanceToSimCache < 1852 * 10)
        {
            return "Less than 10 nm away";
        }
        else if (m_distanceToSimCache < 1852 * 25)
        {
            return "Less than 25 nm away";
        }
        else if (m_distanceToSimCache < 1852 * 50)
        {
            return "Less than 50 nm away";
        }
        return "Greater than 50 nm away";
    }
private:
    ULONG m_RefCount;
    UINT32 m_containerId;

    // Declare member variables representing SIMCACHE state    
    double m_distanceToSimCache;

    ENUM m_unitsRadians;
    ENUM m_unitsMeters;
    ENUM m_aircraftVarLatitude;
    ENUM m_aircraftVarLongitude;
    ENUM m_aircraftVarAltitude;
};