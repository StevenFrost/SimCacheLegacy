//
//  SimCache.cpp
//

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define _CRT_RAND_S
#include "gauges.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "SimConnect.h"

#include "SimCache.h"
#include "SimCacheManager.h"
#include "Transformations.h"
#include "VectorR3.h"

GAUGE_CALLBACK gauge_callback;

// Note: The items in the property table correspond to the indices that
// will be returned in the Get/Set Property functions
struct PROPERTY_TABLE
{
    PCSTRINGZ szPropertyName;
    PCSTRINGZ szUnitsName;
    ENUM units;
};

// 
// PanelCallback is an abstract base class that can be overrided.  Implementors
// should override the functions CreateAircraftCallback(UINT32 ContainerId) as
// well as GetPropertyTable.
class PanelCallback : public IPanelCCallback
{
    DECLARE_PANEL_CALLBACK_REFCOUNT(PanelCallback);

public:
    PanelCallback();

    // ******* IPanelCCallback Methods *****************    
    IPanelCCallback* QueryInterface(PCSTRINGZ pszInterface);
    UINT32 GetVersion();
    bool ConvertStringToProperty(PCSTRINGZ keyword, SINT32* pID);
    bool ConvertPropertyToString(SINT32 id, PPCSTRINGZ pKeyword);
    bool GetPropertyUnits(SINT32 id, ENUM* pEnum);

protected:
    // ******** PanelCallback Methods ******************
    virtual const PROPERTY_TABLE *GetPropertyTable(UINT &uLength) = 0;
};

// 
// AircraftCallback is an abstract base class that can be overrided.  Implementors
// should override the function CreateGaugeCCallback(UINT32 ContainerId)
class AircraftCallback : public IAircraftCCallback
{
    DECLARE_PANEL_CALLBACK_REFCOUNT(AircraftCallback);
public:
    AircraftCallback(UINT32 containerId);

    // ******* IAircraftCCallback Methods ************* 
    IAircraftCCallback* QueryInterface(PCSTRINGZ pszInterface);
    void Update();

protected:
    UINT32 GetContainerId() const;

private:
    UINT32 m_containerId;
};
// End of paneldefs.h
DEFINE_PANEL_CALLBACK_REFCOUNT(PanelCallback);

PanelCallback::PanelCallback()
    : m_RefCount(1)
{
}

IPanelCCallback* PanelCallback::QueryInterface(PCSTRINGZ pszInterface)
{
    return NULL;
}

UINT32 PanelCallback::GetVersion()
{
    return 1;
}

bool PanelCallback::ConvertStringToProperty(PCSTRINGZ keyword, SINT32* pID)
{
    if (!keyword)
    {
        return false;
    }
    if (!pID)
    {
        return false;
    }

    UINT uNumProperties;
    const PROPERTY_TABLE *parPropertyTable = GetPropertyTable(uNumProperties);

    for (UINT i = 0; i < uNumProperties; i++)
    {
        if (_stricmp(parPropertyTable[i].szPropertyName, keyword) == 0)
        {
            *pID = i;
            return true;
        }
    }
    return false;
}

bool PanelCallback::ConvertPropertyToString(SINT32 id, PPCSTRINGZ pKeyword)
{
    if (!pKeyword)
    {
        return false;
    }

    UINT uNumProperties;
    const PROPERTY_TABLE *parPropertyTable = GetPropertyTable(uNumProperties);

    if (id < 0 || id >= (SINT32)uNumProperties)
    {
        return false;
    }
    *pKeyword = parPropertyTable[id].szPropertyName;
    return true;
}

bool PanelCallback::GetPropertyUnits(SINT32 id, ENUM* pEnum)
{
    if (!pEnum)
    {
        return false;
    }

    UINT uNumProperties;
    const PROPERTY_TABLE *parPropertyTable = GetPropertyTable(uNumProperties);

    if (id < 0 || id >= (SINT32)uNumProperties)
    {
        return false;
    }

    *pEnum = parPropertyTable[id].units;
    return true;
}


DEFINE_PANEL_CALLBACK_REFCOUNT(AircraftCallback);

AircraftCallback::AircraftCallback(UINT32 containerId)
    : m_containerId(containerId),
    m_RefCount(1)
{
}

IAircraftCCallback* AircraftCallback::QueryInterface(PCSTRINGZ pszInterface)
{
    return NULL;
}

void AircraftCallback::Update()
{
}

UINT32 AircraftCallback::GetContainerId() const
{
    return m_containerId;
}

//----------------------------------------------------------------------------
// Static Variables
//----------------------------------------------------------------------------
static const char SIMCACHE_CALLBACK_NAME[] = "SIMCACHE";

static PROPERTY_TABLE SIMCACHE_PROPERTY_TABLE[] =
{
    { "Distance", "Number", UNITS_UNKNOWN },
    { "Name", "String", UNITS_STRING },
    { "Status", "String", UNITS_STRING }
};
// Enum that contains the properties 
enum SIMCACHE_VAR
{
    SIMCACHE_VAR_DISTANCE,
    SIMCACHE_VAR_NAME,
    SIMCACHE_VAR_STATUS,
};

HANDLE hSimConnect;

//
// Class that implements IGaugeCCallback
//
class SIMCACHEGaugeCallback : public IGaugeCCallback
{
    DECLARE_PANEL_CALLBACK_REFCOUNT(SIMCACHEGaugeCallback);

    // Declare member variables representing SIMCACHE state    
    double m_distanceToSimCache;

    ENUM m_unitsRadians;
    ENUM m_unitsMeters;
    ENUM m_aircraftVarLatitude;
    ENUM m_aircraftVarLongitude;
    ENUM m_aircraftVarAltitude;

public:
    SIMCACHEGaugeCallback(UINT32 containerId);

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
    UINT32 m_containerId;
};

DEFINE_PANEL_CALLBACK_REFCOUNT(SIMCACHEGaugeCallback)

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

//
// PanelCallback Override
//
class SIMCACHEPanelCallback : public PanelCallback
{
public:
    SIMCACHEPanelCallback::SIMCACHEPanelCallback()
    {
        // init property table
        for (int n = 0; n < 5; n++)
        {
            if (ImportTable.PANELSentry.fnptr != NULL && SIMCACHE_PROPERTY_TABLE[n].units == UNITS_UNKNOWN)
            {
                SIMCACHE_PROPERTY_TABLE[n].units = get_units_enum(SIMCACHE_PROPERTY_TABLE[n].szUnitsName);
            }
        }
    }

    IAircraftCCallback* CreateAircraftCCallback(UINT32 ContainerID)
    {
        return new SIMCACHEAircraftCallback(ContainerID);
    }

protected:
    const PROPERTY_TABLE *GetPropertyTable(UINT &uLength)
    {
        uLength = LENGTHOF(SIMCACHE_PROPERTY_TABLE);
        return SIMCACHE_PROPERTY_TABLE;
    }
};

void SIMCACHEPanelCallbackInit()
{
    SIMCACHEPanelCallback *pPanelCallback = new SIMCACHEPanelCallback();

    if (pPanelCallback)
    {
        bool b = panel_register_c_callback(SIMCACHE_CALLBACK_NAME, pPanelCallback);
        pPanelCallback->Release();
    }
}

void SIMCACHEPanelCallbackDeInit()
{
    panel_register_c_callback(SIMCACHE_CALLBACK_NAME, NULL);
}

// The Panels pointer will get filled in during the loading process
// if this DLL is listed in DLL.XML
PPANELS Panels = NULL;

GAUGESIMPORT ImportTable =
{
    { 0x0000000F, (PPANELS)NULL },
    { 0x00000000, NULL }
};

enum EVENT_ID {
    EVENT_C_LEFT_BRACKET,
    EVENT_C_RIGHT_BRACKET,
    EVENT_C_H,
    EVENT_DISPLAY_TEXT
};
enum DATA_REQUEST_ID {
    REQUEST_CREATE_SIMCACHE,
    REQUEST_REMOVE_SIMCACHE
};

enum GROUP_ID {
    GROUP_SIMCACHE
};

enum INPUT_ID {
    INPUT_SIMCACHE
};

void CALLBACK MyDispatchProcDLL(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext)
{
    switch (pData->dwID)
    {
    case SIMCONNECT_RECV_ID_OPEN:
    {
        auto initPos = SimCache::Manager::Instance().CurrentCache()->InitPosition();
        SimConnect_AICreateSimulatedObject(hSimConnect, "Aerocache", initPos, REQUEST_CREATE_SIMCACHE);
    }
    break;
    default:
        break;
    }
}

void FSAPI module_init(void)
{
    if (NULL != Panels)
    {
        ImportTable.PANELSentry.fnptr = (PPANELS)Panels;
        SIMCACHEPanelCallbackInit();
    }

    auto hr = SimConnect_Open(&hSimConnect, "SimCache", NULL, 0, 0, 0);

    if (hr == S_OK)
    {
        hr = SimConnect_CallDispatch(hSimConnect, MyDispatchProcDLL, NULL);
    }
}

void FSAPI module_deinit(void)
{
    SIMCACHEPanelCallbackDeInit();
    SimConnect_Close(hSimConnect);
}

BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
    return TRUE;
}

// This is the module's export table.
GAUGESLINKAGE Linkage =
{
    0x00000013,
    module_init,
    module_deinit,
    0,
    0,

    FS9LINK_VERSION, { 0 }
};

// 
// end of SIMCACHE.cpp
//
