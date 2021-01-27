// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "RenderManager.h"
#include "RenderCrashFixer.h"

static RenderManager* renderManager;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        Configuration::ReadConfig();
        renderManager = new RenderManager();
        if (Configuration::GetEnableRenderOverflowCrashFix())
        {
            ReplaceMemoryCalls();
        }
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        delete renderManager;
    }

    return TRUE;
}