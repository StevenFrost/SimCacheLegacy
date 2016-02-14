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

#include <CacheManager/CacheManager.h>

namespace SimCache
{

//-----------------------------------------------------------------------------

void CacheManager::SetOnCacheChanged(std::function<void(ICache::Ptr const&)> const& f)
{
    m_onCacheChanged = std::make_shared<std::function<void(ICache::Ptr const&)>>(f);
}

//-----------------------------------------------------------------------------

void CacheManager::AddCache(ICache::Ptr const& cacheToAdd)
{
    m_caches.push_back(ICache::Ptr(cacheToAdd));
}

//-----------------------------------------------------------------------------

ICache::Ptr CacheManager::NextCache()
{
    if (m_currentCache != --m_caches.end())
    {
        ++m_currentCache;
    }
    else
    {
        m_currentCache = m_caches.begin();
    }

    OnCacheChanged();
    return *m_currentCache;
}

//-----------------------------------------------------------------------------

ICache::Ptr CacheManager::PreviousCache()
{
    if (m_currentCache != m_caches.begin())
    {
        --m_currentCache;
    }
    else
    {
        m_currentCache = --m_caches.end();
    }

    OnCacheChanged();
    return *m_currentCache;
}

//-----------------------------------------------------------------------------

ICache::Ptr CacheManager::CurrentCache() const
{
    if (m_currentCache == m_caches.end())
    {
        return nullptr;
    }
    return *m_currentCache;
}

//-----------------------------------------------------------------------------

void CacheManager::OnCacheChanged()
{
    if (m_onCacheChanged != nullptr)
    {
        (*m_onCacheChanged)(*m_currentCache);
    }
}

//-----------------------------------------------------------------------------

} // namespace SimCache
