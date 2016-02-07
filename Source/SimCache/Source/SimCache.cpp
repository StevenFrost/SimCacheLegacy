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
#include <math.h>
#include <windows.h>

#include <SimConnect.h>

#include "PanelCallback.h"
#include "AircraftCallback.h"
#include "SimCacheGaugeCallback.h"
#include "SimCacheAircraftCallback.h"
#include "SimCachePanelCallback.h"

#include "Cache.h"
#include "CacheManager.h"
#include "Transformations.h"
#include "VectorR3.h"

namespace SimCache
{

//-----------------------------------------------------------------------------

static const char SIMCACHE_CALLBACK_NAME[] = "SIMCACHE";

GAUGE_CALLBACK g_gaugeCallback;
HANDLE         g_simConnect = nullptr;

//-----------------------------------------------------------------------------

void PanelCallbackInit()
{
    SimCachePanelCallback *panelCallback = new SimCachePanelCallback();

    if (panelCallback)
    {
        BOOL result = panel_register_c_callback(SIMCACHE_CALLBACK_NAME, panelCallback);
        UNREFERENCED_PARAMETER(result);

        panelCallback->Release();
    }
}

void PanelCallbackDeInit()
{
    panel_register_c_callback(SIMCACHE_CALLBACK_NAME, nullptr);
}

//-----------------------------------------------------------------------------

enum EventID
{
    EVENT_SIM_START,
    EVENT_DISPLAY_TEXT,
    EVENT_PREV_SIMCACHE,
    EVENT_NEXT_SIMCACHE,
    EVENT_SIMCACHE_HINT
};

enum GroupID
{
    GROUP_SIMCACHE
};

enum InputID
{
    INPUT_SIMCACHE
};

//-----------------------------------------------------------------------------

void DisplayText(SIMCONNECT_TEXT_TYPE textType, float durationSeconds, std::string const& text)
{
    SimConnect_Text(g_simConnect, textType, durationSeconds, EVENT_DISPLAY_TEXT, text.size() + 1, (void*)text.c_str());
}

//-----------------------------------------------------------------------------

} // namespace SimCache

//-----------------------------------------------------------------------------

GAUGESIMPORT ImportTable =
{
    { 0x0000000F, (PPANELS)nullptr },
    { 0x00000000, nullptr }
};

PPANELS Panels = nullptr; // filled in during the loading process if this DLL is listed in DLL.XML

//-----------------------------------------------------------------------------

void CALLBACK MyDispatchProcDLL(SIMCONNECT_RECV* data, DWORD callbackData, void* context)
{
    switch (data->dwID)
    {
    case SIMCONNECT_RECV_ID_OPEN:
    {
        SimConnect_MapClientEventToSimEvent(SimCache::g_simConnect, SimCache::EVENT_PREV_SIMCACHE);
        SimConnect_MapClientEventToSimEvent(SimCache::g_simConnect, SimCache::EVENT_NEXT_SIMCACHE);
        SimConnect_MapClientEventToSimEvent(SimCache::g_simConnect, SimCache::EVENT_SIMCACHE_HINT);

        SimConnect_MapInputEventToClientEvent(SimCache::g_simConnect, SimCache::INPUT_SIMCACHE, "Ctrl+F5", SimCache::EVENT_PREV_SIMCACHE);
        SimConnect_MapInputEventToClientEvent(SimCache::g_simConnect, SimCache::INPUT_SIMCACHE, "Ctrl+F6", SimCache::EVENT_SIMCACHE_HINT);
        SimConnect_MapInputEventToClientEvent(SimCache::g_simConnect, SimCache::INPUT_SIMCACHE, "Ctrl+F7", SimCache::EVENT_NEXT_SIMCACHE);
        
        SimConnect_SetInputGroupState(SimCache::g_simConnect, SimCache::INPUT_SIMCACHE, SIMCONNECT_STATE_OFF);

        SimConnect_AddClientEventToNotificationGroup(SimCache::g_simConnect, SimCache::GROUP_SIMCACHE, SimCache::EVENT_PREV_SIMCACHE);
        SimConnect_AddClientEventToNotificationGroup(SimCache::g_simConnect, SimCache::GROUP_SIMCACHE, SimCache::EVENT_NEXT_SIMCACHE);
        SimConnect_AddClientEventToNotificationGroup(SimCache::g_simConnect, SimCache::GROUP_SIMCACHE, SimCache::EVENT_SIMCACHE_HINT);

        SimConnect_SubscribeToSystemEvent(SimCache::g_simConnect, SimCache::EVENT_SIM_START, "SimStart");
        break;
    }
    case SIMCONNECT_RECV_ID_EVENT:
    {
        SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)data;

        switch (evt->uEventID)
        {
        case SimCache::EVENT_SIM_START:
        {
            SimConnect_SetInputGroupState(SimCache::g_simConnect, SimCache::INPUT_SIMCACHE, SIMCONNECT_STATE_ON);
            SimCache::Manager::Instance().DisplayCache(SimCache::Manager::Instance().CurrentCache());
            break;
        }
        case SimCache::EVENT_PREV_SIMCACHE:
        {
            SimCache::Manager::Instance().DisplayCache(SimCache::Manager::Instance().PreviousCache());
            break;
        }
        case SimCache::EVENT_NEXT_SIMCACHE:
        {
            SimCache::Manager::Instance().DisplayCache(SimCache::Manager::Instance().NextCache());
            break;
        }
        case SimCache::EVENT_SIMCACHE_HINT:
        {
            SimCache::DisplayText(SIMCONNECT_TEXT_TYPE_PRINT_WHITE, 15.0f, SimCache::Manager::Instance().CurrentCache()->Hint());
            break;
        }
        }
        break;
    }
    case SIMCONNECT_RECV_ID_ASSIGNED_OBJECT_ID:
    {
        SimCache::Manager::Instance().OnRecvAssignedObjectId((SIMCONNECT_RECV_ASSIGNED_OBJECT_ID*)data);
        break;
    }
    default:
        break;
    }
}

//-----------------------------------------------------------------------------

void FSAPI module_init(void)
{
    if (Panels != nullptr)
    {
        ImportTable.PANELSentry.fnptr = (PPANELS)Panels;
        SimCache::PanelCallbackInit();
    }

    HRESULT hr = SimConnect_Open(&SimCache::g_simConnect, "SimCache", nullptr, 0, 0, 0);

    if (hr == S_OK)
    {
        SimCache::Manager::Instance().SetSimConnect(SimCache::g_simConnect);
        hr = SimConnect_CallDispatch(SimCache::g_simConnect, MyDispatchProcDLL, nullptr);
    }
}

//-----------------------------------------------------------------------------

void FSAPI module_deinit(void)
{
    SimCache::PanelCallbackDeInit();
    SimConnect_Close(SimCache::g_simConnect);
}

//-----------------------------------------------------------------------------

BOOL WINAPI DllMain(HINSTANCE dll, DWORD reason, LPVOID reserved)
{
    return TRUE;
}

//-----------------------------------------------------------------------------

GAUGESLINKAGE Linkage =
{
    0x00000013,
    module_init,
    module_deinit,
    0,
    0,
    FS9LINK_VERSION,
    { 0 }
};

//-----------------------------------------------------------------------------
