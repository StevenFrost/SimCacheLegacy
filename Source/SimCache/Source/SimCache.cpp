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
    EVENT_C_LEFT_BRACKET,
    EVENT_C_RIGHT_BRACKET,
    EVENT_C_H,
    EVENT_DISPLAY_TEXT
};
enum DATA_REQUEST_ID {
    REQUEST_CREATE_SIMCACHE,
    REQUEST_REMOVE_SIMCACHE
};

enum GROUP_ID {
    GROUP_SIMCACHE
};

enum INPUT_ID {
    INPUT_SIMCACHE
};

void CALLBACK MyDispatchProcDLL(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext)
{
    switch (pData->dwID)
    {
    case SIMCONNECT_RECV_ID_OPEN:
    {
        auto initPos = SimCache::Manager::Instance().CurrentCache()->InitPosition();
        SimConnect_AICreateSimulatedObject(hSimConnect, "SimCache", initPos, REQUEST_CREATE_SIMCACHE);
    }
    break;
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
