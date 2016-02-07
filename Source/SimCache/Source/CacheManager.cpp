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

#include "CacheManager.h"

namespace SimCache
{

void Manager::SetSimConnect(HANDLE hSimConnect)
{
    m_hSimConnect = hSimConnect;
}

void Manager::OnRecvAssignedObjectId(SIMCONNECT_RECV_ASSIGNED_OBJECT_ID * pObjData)
{
    switch (pObjData->dwRequestID)
    {
    case REQUEST_CREATE_SIMCACHE:
        m_currentCacheId = pObjData->dwObjectID;
        break;
    }
}

void Manager::DisplayCache(ICache::Ptr const & cacheToDisplay)
{
    if (m_currentCacheId != 0UL)
    {
        SimConnect_AIRemoveObject(m_hSimConnect, m_currentCacheId, REQUEST_REMOVE_SIMCACHE);
    }
    SimConnect_AICreateSimulatedObject(m_hSimConnect, "SimCache", cacheToDisplay->InitPosition(), REQUEST_CREATE_SIMCACHE);
}

void Manager::AddCache(ICache::Ptr const& cacheToAdd)
{
    m_caches.push_back(ICache::Ptr(cacheToAdd));
}

ICache::Ptr Manager::NextCache()
{
    if (m_currentCache != --m_caches.end())
    {
        ++m_currentCache;
    }
    else
    {
        m_currentCache = m_caches.begin();
    }
    return *m_currentCache;
}

ICache::Ptr Manager::PreviousCache()
{
    if (m_currentCache != m_caches.begin())
    {
        --m_currentCache;
    }
    else
    {
        m_currentCache = --m_caches.end();
    }
    return *m_currentCache;
}

}