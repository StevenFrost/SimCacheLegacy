#pragma once

#include "gauges.h"

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
public:
    PanelCallback();

    ULONG AddRef();
    ULONG Release();

    // ******* IPanelCCallback Methods *****************    
    IPanelCCallback* QueryInterface(PCSTRINGZ pszInterface);
    UINT32 GetVersion();
    bool ConvertStringToProperty(PCSTRINGZ keyword, SINT32* pID);
    bool ConvertPropertyToString(SINT32 id, PPCSTRINGZ pKeyword);
    bool GetPropertyUnits(SINT32 id, ENUM* pEnum);

protected:
    // ******** PanelCallback Methods ******************
    virtual const PROPERTY_TABLE *GetPropertyTable(UINT &uLength) = 0;

private:
    ULONG m_RefCount;
};