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
    {
        AddCache(Factory::Make("Friday Harbor Airport", 48.5219722, -123.0243611, 112.7));
        m_currentCache = m_caches.begin();
    };

    std::vector<ICache::Ptr> m_caches;
    std::vector<ICache::Ptr>::iterator m_currentCache;
};

//-----------------------------------------------------------------------------

} // namespace SimCache
