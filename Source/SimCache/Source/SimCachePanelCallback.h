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

#include <gauges.h>
#include <sal.h>

#include "PanelCallback.h"
#include "SimCacheAircraftCallback.h"

namespace SimCache
{

//-----------------------------------------------------------------------------

static const unsigned int NUM_SIMCACHE_PROPERTIES = 5;
static PropertyTableRow SIMCACHE_PROPERTY_TABLE[NUM_SIMCACHE_PROPERTIES] =
{
    { "Distance", "Number", UNITS_UNKNOWN },
    { "Name",     "String", UNITS_STRING  },
    { "Hint",     "String", UNITS_STRING  },
    { "Status",   "String", UNITS_STRING  },
    { "Index",    "Number", UNITS_UNKNOWN }
};

//-----------------------------------------------------------------------------

class SimCachePanelCallback : public PanelCallback
{
public:
    SimCachePanelCallback()
    {
        for (int n = 0; n < NUM_SIMCACHE_PROPERTIES; n++)
        {
            if (ImportTable.PANELSentry.fnptr != NULL && SIMCACHE_PROPERTY_TABLE[n].Units == UNITS_UNKNOWN)
            {
                SIMCACHE_PROPERTY_TABLE[n].Units = get_units_enum(SIMCACHE_PROPERTY_TABLE[n].UnitsName);
            }
        }
    }

    IAircraftCCallback* CreateAircraftCCallback(UINT32 containerID)
    {
        return new SimCacheAircraftCallback(containerID);
    }

protected:
    const PropertyTableRow *GetPropertyTable(_Out_ UINT &length)
    {
        length = LENGTHOF(SIMCACHE_PROPERTY_TABLE);
        return SIMCACHE_PROPERTY_TABLE;
    }
};

//-----------------------------------------------------------------------------

} // namespace SimCache
