// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "TerrainRenderProxyInjector.h"

static TerrainRenderProxyInjector* Injector;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        Injector = new TerrainRenderProxyInjector();
        Injector->Inject();
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        delete Injector;
    }

    return TRUE;
}