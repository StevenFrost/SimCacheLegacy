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

#include <memory>
#include <vector>
#include <windows.h>

#include <SimConnect.h>

#include "Cache.h"

namespace SimCache
{

//-----------------------------------------------------------------------------

enum DataRequestID
{
    REQUEST_CREATE_SIMCACHE,
    REQUEST_REMOVE_SIMCACHE
};

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

    void SetSimConnect(HANDLE simConnect);
    void OnRecvAssignedObjectId(SIMCONNECT_RECV_ASSIGNED_OBJECT_ID *objData);
    void DisplayCache(ICache::Ptr const& cacheToDisplay);

    void AddCache(ICache::Ptr const& cacheToAdd);

    ICache::Ptr NextCache();
    ICache::Ptr PreviousCache();
    ICache::Ptr CurrentCache() const;

private:
    Manager() :
        m_simConnect(nullptr),
        m_currentCacheId(0UL)
    {
        AddCache(Factory::Make("Friday Harbor Airport", "This airport is the starting point for the Flight Simulator X default flight.", 48.5219722, -123.0243611, 112.7, 1000.0, 50.0));
        AddCache(Factory::Make("Meigs Field", "This airport was the starting point for default flights for all previous versions of Microsoft Flight Simulator.", 41.86, -87.608611, 593.0, 1000.0, 50.0));
        AddCache(Factory::Make("Jackson Hole Airport", "This airport is the only commercial airport within a U.S. National Park.", 43.6073333, -110.7377500, 6451.0, 1000.0, 50.0));
        AddCache(Factory::Make("Shuttle Landing Facility", "This airport was the primary landing site for the Space Shuttle and has one of the longest runways in the world, at 15,000 ft long and 300 ft wide.", 28.6148889, -80.6943611, 8.5, 1000.0, 50.0));
        AddCache(Factory::Make("First Flight Airport", "This airport is famous for being the site of hundreds of pre-flight gliding experiments carried out by the Wright brothers.", 36.0175833, -75.6715833, 11.9, 1000.0, 50.0));
        m_currentCache = m_caches.begin();
    };

    std::vector<ICache::Ptr> m_caches;
    std::vector<ICache::Ptr>::iterator m_currentCache;

    HANDLE m_simConnect;
    unsigned long m_currentCacheId;
};

//-----------------------------------------------------------------------------

} // namespace SimCache
