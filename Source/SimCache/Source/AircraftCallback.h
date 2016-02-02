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

// AircraftCallback is an abstract base class that can be overrided.  Implementors
// should override the function CreateGaugeCCallback(UINT32 ContainerId)
class AircraftCallback : public IAircraftCCallback
{
public:
    AircraftCallback(UINT32 containerId);
    virtual ~AircraftCallback() {}

    virtual ULONG AddRef();
    virtual ULONG Release();

    virtual IAircraftCCallback* QueryInterface(PCSTRINGZ pszInterface);
    virtual void Update();

protected:
    UINT32 GetContainerId() const;

private:
    ULONG  m_refCount;
    UINT32 m_containerId;
};