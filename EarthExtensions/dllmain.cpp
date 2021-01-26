// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "TerrainRenderProxyInjector.h"
#include "ShadowRenderProxyInjector.h"
#include "WaterRenderProxyInjector.h"
#include "RenderManager.h"

static TerrainRenderProxyInjector* TerrainInjector;
static ShadowRenderProxyInjector* ShadowInjector;
static RenderManager* renderManager;

static byte antiCrash[] = {
    0x81, 0xFE, 0xF0, 0xFF, 0x00, 0x00,         //cmp    esi,0xfff0
    0x0F, 0x8D, 0x30, 0x12, 0x00, 0x00,         //jge    123c <_main + 0x123c>
    0x85, 0xF6,                                 //test   esi,esi
    0x0F, 0x85, 0x30, 0x12, 0x00, 0x00,         //jne    1244 < _main + 0x1244 >
    0xE9, 0x30, 0x12, 0x00, 0x00,               //jmp    1249 < _main + 0x1249 >
};

void HookAntiCrash()
{
    const ULONG_PTR loopBeginAddress = 0x00614AC1;
    const ULONG_PTR loopEndAddress = 0x00614FB1;
    ULONG jmp1RelativeAddress = (ULONG)loopEndAddress - (ULONG)(&antiCrash) - 12;
    ULONG jmp2RelativeAddress = (ULONG)loopBeginAddress - (ULONG)(&antiCrash) - 20;
    ULONG jmp3RelativeAddress = (ULONG)loopEndAddress - (ULONG)(&antiCrash) - 25 ;

    byte jmpBytes1[4];
    ToByteArray(jmp1RelativeAddress, jmpBytes1);
    byte jmpBytes2[4];
    ToByteArray(jmp2RelativeAddress, jmpBytes2);
    byte jmpBytes3[4];
    ToByteArray(jmp3RelativeAddress, jmpBytes3);
    antiCrash[8]  = jmpBytes1[3];
    antiCrash[9]  = jmpBytes1[2];
    antiCrash[10] = jmpBytes1[1];
    antiCrash[11] = jmpBytes1[0];
    antiCrash[16] = jmpBytes2[3];
    antiCrash[17] = jmpBytes2[2];
    antiCrash[18] = jmpBytes2[1];
    antiCrash[19] = jmpBytes2[0];
    antiCrash[21] = jmpBytes3[3];
    antiCrash[22] = jmpBytes3[2];
    antiCrash[23] = jmpBytes3[1];
    antiCrash[24] = jmpBytes3[0];

    const ULONG_PTR injectAddress = 0x00614FA9;
    ULONG relativeAddress = (ULONG)(&antiCrash) - 5 - (ULONG)injectAddress;
    byte bytes[4];
    ToByteArray(relativeAddress, bytes);
    byte proxyCall[] = {
        0xE9, bytes[3], bytes[2], bytes[1], bytes[0],       //call ${relativeAddress}
        0x90,                                               //nop
        0x90,                                               //nop
        0x90                                                //nop
    };

    WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

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
        renderManager = new RenderManager();
        HookAntiCrash();
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        delete TerrainInjector;
        delete ShadowInjector;
        delete renderManager;
    }

    return TRUE;
}