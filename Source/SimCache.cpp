//
//  SimCache.cpp
//

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define _CRT_RAND_S
#include "gauges.h"

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
    bool ConvertStringToProperty (PCSTRINGZ keyword, SINT32* pID);
    bool ConvertPropertyToString (SINT32 id, PPCSTRINGZ pKeyword);
    bool GetPropertyUnits (SINT32 id, ENUM* pEnum);

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
    if(!keyword)
    {
        return false;
    }
    if(!pID)
    {
        return false;
    }

    UINT uNumProperties;
    const PROPERTY_TABLE *parPropertyTable = GetPropertyTable(uNumProperties);
    
    for(UINT i = 0; i < uNumProperties; i++)
    {
        if(_stricmp(parPropertyTable[i].szPropertyName, keyword) == 0)
        {
            *pID = i;
            return true;
        }
    }
    return false;         
}

bool PanelCallback::ConvertPropertyToString (SINT32 id, PPCSTRINGZ pKeyword)
{
    if(!pKeyword)
    {
        return false;
    }
    
    UINT uNumProperties;
    const PROPERTY_TABLE *parPropertyTable = GetPropertyTable(uNumProperties);

    if(id < 0 || id >= (SINT32)uNumProperties)
    {
        return false;
    }
    *pKeyword = parPropertyTable[id].szPropertyName;
    return true; 
}

bool PanelCallback::GetPropertyUnits (SINT32 id, ENUM* pEnum)
{
    if(!pEnum)
    {
        return false;
    }

    UINT uNumProperties;
    const PROPERTY_TABLE *parPropertyTable = GetPropertyTable(uNumProperties);
    
    if(id < 0 || id >= (SINT32)uNumProperties)
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
    { "Distance", "Number", UNITS_UNKNOWN},
};
// Enum that contains the properties 
enum SIMCACHE_VAR
{
    SIMCACHE_VAR_DISTANCE,
};

//
// Class that implements IGaugeCCallback
//
class SIMCACHEGaugeCallback : public IGaugeCCallback
{
    DECLARE_PANEL_CALLBACK_REFCOUNT(SIMCACHEGaugeCallback);

    // Declare member variables representing SIMCACHE state
    double m_simcacheLat;
    double m_simcacheLon;
    double m_distanceToSimCache;

public:
    SIMCACHEGaugeCallback(UINT32 containerId); 

    // ************* IGaugeCCallback Methods ***************
    IGaugeCCallback* QueryInterface(PCSTRINGZ pszInterface);
    void Update();
    bool GetPropertyValue (SINT32 id, FLOAT64* pValue);
    bool GetPropertyValue (SINT32 id, PCSTRINGZ* pszValue);
    bool SetPropertyValue (SINT32 id, FLOAT64 value);
    bool SetPropertyValue (SINT32 id, PCSTRINGZ szValue);
    IGaugeCDrawable* CreateGaugeCDrawable(SINT32 id, const IGaugeCDrawableCreateParameters* pParameters);
    
    double getSimCacheDistance()
    {
        return m_distanceToSimCache;
    }
private:
    UINT32 m_containerId;
};

double distance_func_of_awesomeness(double lat1, double lon1, double lat2, double lon2)
{
    auto lat1r = M_PI * lat1 / 180.0;
    auto lon1r = M_PI * lon1 / 180.0;
    auto lat2r = M_PI * lat2 / 180.0;
    auto lon2r = M_PI * lon2 / 180.0;

    auto theta = lon1 - lon2;
    auto thetar = M_PI * theta / 180.0;

    auto dist = sin(lat1r) * sin(lat2r) + cos(lat1r) * cos(lat2r) * cos(thetar);
    dist = acos(dist);
    dist = dist * 180 / M_PI;
    dist = dist * 60 * 1.1515;
    dist = dist * 0.8684;

    return dist;
}

DEFINE_PANEL_CALLBACK_REFCOUNT(SIMCACHEGaugeCallback)

SIMCACHEGaugeCallback::SIMCACHEGaugeCallback(UINT32 containerId)
    : m_RefCount(1),
      m_containerId(containerId),
      m_distanceToSimCache(1.0f)
{
    // Friday Harbor Airport
    m_simcacheLat = 48.521944;
    m_simcacheLon = -123.024444;
}

IGaugeCCallback* SIMCACHEGaugeCallback::QueryInterface(PCSTRINGZ pszInterface)
{
    return NULL;
}

//
// The Update functions is called on a 18Hz cycle
//
void SIMCACHEGaugeCallback::Update()
{
    FLOAT64 currentLat = aircraft_varget(get_aircraft_var_enum("PLANE LATITUDE"), get_units_enum("degrees"), 0);
    FLOAT64 currentLon = aircraft_varget(get_aircraft_var_enum("PLANE LONGITUDE"), get_units_enum("degrees"), 0);

    m_distanceToSimCache = distance_func_of_awesomeness(m_simcacheLat, m_simcacheLon, currentLat, currentLon);
}

//
// Getting float/numeric values
//
bool SIMCACHEGaugeCallback::GetPropertyValue (SINT32 id, FLOAT64* pValue)
{
    if(!pValue)
    {
       return false;
    }

    *pValue = 1.0;      // Start with a reasonable default
    SIMCACHE_VAR eSIMCACHEVar = (SIMCACHE_VAR)id;

    switch(eSIMCACHEVar)
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
bool SIMCACHEGaugeCallback::GetPropertyValue (SINT32 id, PCSTRINGZ* pszValue)
{
    return true;
}

//
// Setting float/numeric values
//
bool SIMCACHEGaugeCallback::SetPropertyValue (SINT32 id, FLOAT64 value)
{
    return true; 
}

//
// Setting string values
//
bool SIMCACHEGaugeCallback::SetPropertyValue (SINT32 id, PCSTRINGZ szValue)
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
    SIMCACHEAircraftCallback(UINT32 ContainerID): AircraftCallback(ContainerID)
    {}
    IGaugeCCallback* CreateGaugeCCallback ()
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
            if (ImportTable.PANELSentry.fnptr != NULL &&
                SIMCACHE_PROPERTY_TABLE[n].units == UNITS_UNKNOWN)
            {
                SIMCACHE_PROPERTY_TABLE[n].units = get_units_enum ( SIMCACHE_PROPERTY_TABLE[n].szUnitsName );
            }
        }
    }
    
    IAircraftCCallback* CreateAircraftCCallback (UINT32 ContainerID)
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

    if(pPanelCallback)
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

GAUGESIMPORT    ImportTable =                           
{                                                       
    { 0x0000000F, (PPANELS)NULL },                     
    { 0x00000000, NULL }                                
};                                                      
   
void FSAPI  module_init(void)
{
    if (NULL != Panels)
    {
        ImportTable.PANELSentry.fnptr = (PPANELS)Panels;
        SIMCACHEPanelCallbackInit();
    }
}

void FSAPI  module_deinit(void){
    SIMCACHEPanelCallbackDeInit();
}

BOOL WINAPI DllMain (HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
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
