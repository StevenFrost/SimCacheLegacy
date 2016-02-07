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

#include "gauges.h"
#include "PanelCallback.h"
#include "SimCacheAircraftCallback.h"

static PROPERTY_TABLE SIMCACHE_PROPERTY_TABLE[] =
{
    { "Distance", "Number", UNITS_UNKNOWN },
    { "Name", "String", UNITS_STRING },
    { "Hint", "String", UNITS_STRING },
    { "Status", "String", UNITS_STRING },
    { "Index", "Number", UNITS_UNKNOWN }
};

//
// PanelCallback Override
//
class SIMCACHEPanelCallback : public PanelCallback
{
public:
    SIMCACHEPanelCallback::SIMCACHEPanelCallback()
    {
        // init property table
        for (int n = 0; n < 5; n++)
        {
            if (ImportTable.PANELSentry.fnptr != NULL && SIMCACHE_PROPERTY_TABLE[n].units == UNITS_UNKNOWN)
            {
                SIMCACHE_PROPERTY_TABLE[n].units = get_units_enum(SIMCACHE_PROPERTY_TABLE[n].szUnitsName);
            }
        }
    }

    IAircraftCCallback* CreateAircraftCCallback(UINT32 ContainerID)
    {
        return new SIMCACHEAircraftCallback(ContainerID);
    }

protected:
    const PROPERTY_TABLE *GetPropertyTable(UINT &uLength)
    {
        uLength = LENGTHOF(SIMCACHE_PROPERTY_TABLE);
        return SIMCACHE_PROPERTY_TABLE;
    }
};