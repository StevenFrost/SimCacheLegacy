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

#include "AircraftCallback.h"

ULONG AircraftCallback::AddRef()
{
    return ++m_refCount;
}
ULONG AircraftCallback::Release()
{
    ULONG result = --m_refCount;
    if (result < 1)
        delete this;
    return result;
}

AircraftCallback::AircraftCallback(UINT32 containerId)
    : m_containerId(containerId),
    m_refCount(1)
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