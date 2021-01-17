// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "TerrainRenderProxyInjector.h"
#include "ShadowRenderProxyInjector.h"

static TerrainRenderProxyInjector* TerrainInjector;
static ShadowRenderProxyInjector* ShadowInjector;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        TerrainInjector = new TerrainRenderProxyInjector();
        TerrainInjector->Inject();
        ShadowInjector = new ShadowRenderProxyInjector();
        ShadowInjector->Inject();
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        delete TerrainInjector;
        delete ShadowInjector;
    }

    return TRUE;
}