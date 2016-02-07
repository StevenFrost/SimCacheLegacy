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
#include <sal.h>

namespace SimCache
{

//-----------------------------------------------------------------------------

struct PropertyTableRow
{
    PCSTRINGZ PropertyName;
    PCSTRINGZ UnitsName;
    ENUM      Units;
};

//-----------------------------------------------------------------------------

class PanelCallback : public IPanelCCallback
{
public:
    PanelCallback();

    ULONG AddRef();
    ULONG Release();

    IPanelCCallback* QueryInterface(PCSTRINGZ object) { return nullptr; }
    UINT32 GetVersion();

    bool ConvertStringToProperty(PCSTRINGZ keyword, SINT32 *id);
    bool ConvertPropertyToString(SINT32 id, PPCSTRINGZ keyword);
    bool GetPropertyUnits(SINT32 id, ENUM *units);

protected:
    virtual const PropertyTableRow *GetPropertyTable(_Out_ UINT &length) = 0;

private:
    ULONG m_refCount;
};

//-----------------------------------------------------------------------------

} // namespace SimCache
