#include "CacheManager.h"

namespace SimCache
{

 void Manager::AddCache(ICache::Ptr const& cacheToAdd)
{
    m_caches.push_back(ICache::Ptr(cacheToAdd));
}

ICache::Ptr Manager::NextCache()
{
    if (m_currentCache != m_caches.end())
    {
        m_currentCache++;
        return *m_currentCache;
    }
    else
    {
        m_currentCache = m_caches.begin();
        return *m_currentCache;
    }
}

ICache::Ptr Manager::PreviousCache()
{
    if (m_currentCache != m_caches.begin())
    {
        m_currentCache--;
        return *m_currentCache;
    }
    else
    {
        m_currentCache = m_caches.end();
        return *m_currentCache;
    }
}

}