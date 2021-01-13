// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Direct3DDeviceProxy.h"
#include "TerrainRenderProxyInjector.h"

VOID HookDrawIndexedPrimitive()
{
    const ULONG_PTR injectAddress = 0x005C8F41;
    DrawIndexedPrimitiveAddress = (LPVOID)((ULONG_PTR)DrawIndexedPrimitive);
    void** proxyAddress = &DrawIndexedPrimitiveAddress;
    byte bytes[4];
    bytes[0] = (int)(((ULONG)proxyAddress >> 24) & 0xFF);
    bytes[1] = (int)(((ULONG)proxyAddress >> 16) & 0xFF);
    bytes[2] = (int)(((ULONG)proxyAddress >> 8) & 0XFF);
    bytes[3] = (int)((ULONG)proxyAddress & 0XFF);

    byte proxyCall[] = {
        0x52,                                                   //push edx
        0x50,                                                   //push eax
        0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
        0x90,                                                   //nop
        0x90,                                                   //nop
        0x90,                                                   //nop
        0x90,                                                   //nop
        0x90,                                                   //nop
        0x90                                                    //nop
    };

    WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

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

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}