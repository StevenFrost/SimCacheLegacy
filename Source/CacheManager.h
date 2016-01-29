#pragma once

#include <memory>
#include <vector>

#include "Cache.h"

namespace SimCache
{

//-----------------------------------------------------------------------------

class Manager
{
public:
    static Manager& Instance()
    {
        static Manager instance;
        return instance;
    }

    Manager(Manager const&) = delete;
    void operator=(Manager const&) = delete;

    void AddCache(ICache::Ptr const& cacheToAdd);

    ICache::Ptr NextCache();
    ICache::Ptr PreviousCache();
    ICache::Ptr CurrentCache() const { return *m_currentCache; }

private:
    Manager()
        :
        m_currentCache(m_caches.begin())
    {
        AddCache(Factory::Make("Friday Harbor Airport", 48.5219722, -123.0243611, 112.7));
    };

    std::vector<ICache::Ptr> m_caches;
    std::vector<ICache::Ptr>::iterator m_currentCache;
};

//-----------------------------------------------------------------------------

} // namespace SimCache
