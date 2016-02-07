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

#define _USE_MATH_DEFINES
#include <math.h>

#define _CRT_RAND_S
#include "gauges.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "SimConnect.h"

#include "PanelCallback.h"
#include "AircraftCallback.h"
#include "SimCacheGaugeCallback.h"
#include "SimCacheAircraftCallback.h"
#include "SimCachePanelCallback.h"

#include "Cache.h"
#include "CacheManager.h"
#include "Transformations.h"
#include "VectorR3.h"

GAUGE_CALLBACK gauge_callback;

//----------------------------------------------------------------------------
// Static Variables
//----------------------------------------------------------------------------
static const char SIMCACHE_CALLBACK_NAME[] = "SIMCACHE";

HANDLE hSimConnect;

void SIMCACHEPanelCallbackInit()
{
    SIMCACHEPanelCallback *pPanelCallback = new SIMCACHEPanelCallback();

    if (pPanelCallback)
    {
        BOOL b = panel_register_c_callback(SIMCACHE_CALLBACK_NAME, pPanelCallback);
        UNREFERENCED_PARAMETER(b);

        pPanelCallback->Release();
    }
}

void SIMCACHEPanelCallbackDeInit()
{
    panel_register_c_callback(SIMCACHE_CALLBACK_NAME, NULL);
}

// The Panels pointer will get filled in during the loading process
// if this DLL is listed in DLL.XML
PPANELS Panels = NULL;

GAUGESIMPORT ImportTable =
{
    { 0x0000000F, (PPANELS)NULL },
    { 0x00000000, NULL }
};

enum EVENT_ID {
    EVENT_SIM_START,
    EVENT_DISPLAY_TEXT,
    EVENT_PREV_SIMCACHE,
    EVENT_NEXT_SIMCACHE,
    EVENT_SIMCACHE_HINT
};

enum GROUP_ID {
    GROUP_SIMCACHE
};

enum INPUT_ID {
    INPUT_SIMCACHE
};

void DisplayText(SIMCONNECT_TEXT_TYPE textType, float durationSeconds, std::string const& text)
{
    SimConnect_Text(hSimConnect, textType, durationSeconds, EVENT_DISPLAY_TEXT, text.size() + 1, (void*)text.c_str());
}

void CALLBACK MyDispatchProcDLL(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext)
{
    switch (pData->dwID)
    {
    case SIMCONNECT_RECV_ID_OPEN:
    {
        SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_PREV_SIMCACHE);
        SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_NEXT_SIMCACHE);
        SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_SIMCACHE_HINT);

        SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT_SIMCACHE, "Ctrl+F5", EVENT_PREV_SIMCACHE);
        SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT_SIMCACHE, "Ctrl+F6", EVENT_SIMCACHE_HINT);
        SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT_SIMCACHE, "Ctrl+F7", EVENT_NEXT_SIMCACHE);
        
        SimConnect_SetInputGroupState(hSimConnect, INPUT_SIMCACHE, SIMCONNECT_STATE_OFF);

        SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_SIMCACHE, EVENT_PREV_SIMCACHE);
        SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_SIMCACHE, EVENT_NEXT_SIMCACHE);
        SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_SIMCACHE, EVENT_SIMCACHE_HINT);

        SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_START, "SimStart");
        break;
    }
    case SIMCONNECT_RECV_ID_EVENT:
    {
        SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;

        switch (evt->uEventID)
        {
        case EVENT_SIM_START:
        {
            SimConnect_SetInputGroupState(hSimConnect, INPUT_SIMCACHE, SIMCONNECT_STATE_ON);
            SimCache::Manager::Instance().DisplayCache(SimCache::Manager::Instance().CurrentCache());
            break;
        }
        case EVENT_PREV_SIMCACHE:
        {
            SimCache::Manager::Instance().DisplayCache(SimCache::Manager::Instance().PreviousCache());
            break;
        }
        case EVENT_NEXT_SIMCACHE:
        {
            SimCache::Manager::Instance().DisplayCache(SimCache::Manager::Instance().NextCache());
            break;
        }
        case EVENT_SIMCACHE_HINT:
        {
            DisplayText(SIMCONNECT_TEXT_TYPE_PRINT_WHITE, 15.0f, SimCache::Manager::Instance().CurrentCache()->Hint());
            break;
        }
        }
        break;
    }
    case SIMCONNECT_RECV_ID_ASSIGNED_OBJECT_ID:
    {
        SimCache::Manager::Instance().OnRecvAssignedObjectId((SIMCONNECT_RECV_ASSIGNED_OBJECT_ID*)pData);
        break;
    }
    default:
        break;
    }
}

void FSAPI module_init(void)
{
    if (NULL != Panels)
    {
        ImportTable.PANELSentry.fnptr = (PPANELS)Panels;
        SIMCACHEPanelCallbackInit();
    }

    auto hr = SimConnect_Open(&hSimConnect, "SimCache", NULL, 0, 0, 0);

    if (hr == S_OK)
    {
        SimCache::Manager::Instance().SetSimConnect(hSimConnect);
        hr = SimConnect_CallDispatch(hSimConnect, MyDispatchProcDLL, NULL);
    }
}

void FSAPI module_deinit(void)
{
    SIMCACHEPanelCallbackDeInit();
    SimConnect_Close(hSimConnect);
}

BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
    return TRUE;
}

// This is the module's export table.
GAUGESLINKAGE Linkage =
{
    0x00000013,
    module_init,
    module_deinit,
    0,
    0,

    FS9LINK_VERSION, { 0 }
};
