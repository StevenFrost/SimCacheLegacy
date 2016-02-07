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

#include "PanelCallback.h"

namespace SimCache
{

//-----------------------------------------------------------------------------

PanelCallback::PanelCallback()
    : m_refCount(1)
{}

//-----------------------------------------------------------------------------

ULONG PanelCallback::AddRef()
{
    return ++m_refCount;
}

//-----------------------------------------------------------------------------

ULONG PanelCallback::Release()
{
    ULONG result = --m_refCount;
    if (result < 1)
    {
        delete this;
    }
    return result;
}

//-----------------------------------------------------------------------------

UINT32 PanelCallback::GetVersion()
{
    return 1;
}

//-----------------------------------------------------------------------------

bool PanelCallback::ConvertStringToProperty(PCSTRINGZ keyword, SINT32* id)
{
    if (!keyword)
    {
        return false;
    }
    if (!id)
    {
        return false;
    }

    UINT numProperties;
    const PropertyTableRow *parPropertyTable = GetPropertyTable(numProperties);

    for (UINT i = 0; i < numProperties; i++)
    {
        if (_stricmp(parPropertyTable[i].PropertyName, keyword) == 0)
        {
            *id = i;
            return true;
        }
    }
    return false;
}

//-----------------------------------------------------------------------------

bool PanelCallback::ConvertPropertyToString(SINT32 id, PPCSTRINGZ keyword)
{
    if (!keyword)
    {
        return false;
    }

    UINT numProperties;
    const PropertyTableRow *parPropertyTable = GetPropertyTable(numProperties);

    if (id < 0 || id >= (SINT32)numProperties)
    {
        return false;
    }
    *keyword = parPropertyTable[id].PropertyName;
    return true;
}

//-----------------------------------------------------------------------------

bool PanelCallback::GetPropertyUnits(SINT32 id, ENUM* units)
{
    if (!units)
    {
        return false;
    }

    UINT numProperties;
    const PropertyTableRow *parPropertyTable = GetPropertyTable(numProperties);

    if (id < 0 || id >= (SINT32)numProperties)
    {
        return false;
    }

    *units = parPropertyTable[id].Units;
    return true;
}

//-----------------------------------------------------------------------------

} // namespace SimCache
