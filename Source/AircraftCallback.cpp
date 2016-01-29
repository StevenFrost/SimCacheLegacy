#include "AircraftCallback.h"

ULONG AircraftCallback::AddRef()
{
    return ++m_RefCount;
}
ULONG AircraftCallback::Release()
{
    ULONG result = --m_RefCount;
    if (result < 1)
        delete this;
    return result;
}

AircraftCallback::AircraftCallback(UINT32 containerId)
    : m_containerId(containerId),
    m_RefCount(1)
{}

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