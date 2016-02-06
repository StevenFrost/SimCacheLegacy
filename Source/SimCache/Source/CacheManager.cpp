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