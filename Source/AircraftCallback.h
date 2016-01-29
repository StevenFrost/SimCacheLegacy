#pragma once

#include "gauges.h"

// 
// AircraftCallback is an abstract base class that can be overrided.  Implementors
// should override the function CreateGaugeCCallback(UINT32 ContainerId)
class AircraftCallback : public IAircraftCCallback
{
public:
    AircraftCallback(UINT32 containerId);

    ULONG AddRef();
    ULONG Release();

    // ******* IAircraftCCallback Methods ************* 
    IAircraftCCallback* QueryInterface(PCSTRINGZ pszInterface);
    void Update();

protected:
    UINT32 GetContainerId() const;

private:
    ULONG m_RefCount;
    UINT32 m_containerId;
};