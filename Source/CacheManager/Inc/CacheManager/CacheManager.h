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

#include <functional>
#include <memory>
#include <vector>

#include <CacheManager/Cache.h>

namespace SimCache
{

//-----------------------------------------------------------------------------

class CacheManager
{
public:
    static CacheManager& Instance()
    {
        static CacheManager instance;
        return instance;
    }

    CacheManager(CacheManager const&) = delete;
    void operator=(CacheManager const&) = delete;

    void SetOnCacheChanged(std::function<void(ICache::Ptr const&)> const& f);
    void AddCache(ICache::Ptr const& cacheToAdd);

    ICache::Ptr NextCache();
    ICache::Ptr PreviousCache();
    ICache::Ptr CurrentCache() const;

private:
    CacheManager() :
        m_onCacheChanged(nullptr),
        m_currentCacheId(0UL)
    {
        AddCache(Factory::Make("Friday Harbor Airport", "This airport is the starting point for the Flight Simulator X default flight.", 48.5219722, -123.0243611, 112.7, 1000.0, 50.0));
        AddCache(Factory::Make("Meigs Field", "This airport was the starting point for default flights for all previous versions of Microsoft Flight Simulator.", 41.86, -87.608611, 593.0, 1000.0, 50.0));
        AddCache(Factory::Make("Jackson Hole Airport", "This airport is the only commercial airport within a U.S. National Park.", 43.6073333, -110.7377500, 6451.0, 1000.0, 50.0));
        AddCache(Factory::Make("Shuttle Landing Facility", "This airport was the primary landing site for the Space Shuttle and has one of the longest runways in the world, at 15,000 ft long and 300 ft wide.", 28.6148889, -80.6943611, 8.5, 1000.0, 50.0));
        AddCache(Factory::Make("First Flight Airport", "This airport is famous for being the site of hundreds of pre-flight gliding experiments carried out by the Wright brothers.", 36.0175833, -75.6715833, 11.9, 1000.0, 50.0));
        m_currentCache = m_caches.begin();
    };

    void OnCacheChanged();

private:
    std::shared_ptr<std::function<void(ICache::Ptr const&)>> m_onCacheChanged;

    std::vector<ICache::Ptr> m_caches;
    std::vector<ICache::Ptr>::iterator m_currentCache;

    unsigned long m_currentCacheId;
};

//-----------------------------------------------------------------------------

} // namespace SimCache
