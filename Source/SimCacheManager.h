#pragma once

#include <memory>
#include <vector>

#include "SimCache.h"

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

    void AddCache(ICache::Ptr cacheToAdd);

    void IndexIncrement() { m_index = m_index + 1 > m_simCaches.size() -1 ? 0 : m_index + 1; }
    void IndexDecrement() { m_index = m_index - 1 < 0 ? m_simCaches.size() -1 : m_index - 1; }

    ICache::Ptr CurrentCache() { return m_simCaches[m_index]; }

private:
    Manager()
        :
        m_index(0)
    {
        m_simCaches.push_back(SimCache::Factory::Make("Friday Harbor Airport", 48.5219722, -123.0243611, 112.7));
    };

    std::vector<ICache::Ptr> m_simCaches;
    std::vector<ICache::Ptr>::size_type m_index;
};

//-----------------------------------------------------------------------------

} // namespace SimCache
