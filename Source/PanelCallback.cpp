#include "PanelCallback.h"

ULONG PanelCallback::AddRef()
{
    return ++m_RefCount;
}

ULONG PanelCallback::Release()
{
    ULONG result = --m_RefCount;
    if (result < 1)
        delete this;
    return result;
}

PanelCallback::PanelCallback()
    : m_RefCount(1)
{}

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