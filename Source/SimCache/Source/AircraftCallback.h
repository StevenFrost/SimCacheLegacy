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

namespace SimCache
{

//-----------------------------------------------------------------------------

class AircraftCallback : public IAircraftCCallback
{
public:
    AircraftCallback(UINT32 containerId);
    virtual ~AircraftCallback() {}

    virtual ULONG AddRef();
    virtual ULONG Release();

    virtual IAircraftCCallback* QueryInterface(PCSTRINGZ) { return nullptr; }
    virtual void Update() {}

protected:
    UINT32 GetContainerId() const;

private:
    ULONG  m_refCount;
    UINT32 m_containerId;
};

//-----------------------------------------------------------------------------

} // namespace SimCache
