#include "pch.h"
#include"RenderCrashFixer.h"

static short TerrainRenderBuffer[2+512 * 512];

void ReplaceMemoryCalls()
{
    byte bytes[4];
    ToByteArray((ULONG)TerrainRenderBuffer, bytes);
    byte newAddress[] = { bytes[3], bytes[2], bytes[1], bytes[0] };
    byte bytesPlus2[4];
    ToByteArray(((ULONG)TerrainRenderBuffer)+2, bytesPlus2);
    byte newAddressPlus2[] = { bytesPlus2[3], bytesPlus2[2], bytesPlus2[1], bytesPlus2[0] };
    byte bytesPlus3[4];
    ToByteArray(((ULONG)TerrainRenderBuffer) + 3, bytesPlus3);
    byte newAddressPlus3[] = { bytesPlus3[3], bytesPlus3[2], bytesPlus3[1], bytesPlus3[0] };

    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614AB6, newAddressPlus2, 4, NULL);
    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614AC4, newAddress, 4, NULL);
    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614AD4, newAddressPlus3, 4, NULL);
    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614E35, newAddressPlus2, 4, NULL);
    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614E61, newAddressPlus2, 4, NULL);
    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614E8C, newAddressPlus2, 4, NULL);
    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614EB8, newAddressPlus2, 4, NULL);
    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614EE4, newAddressPlus2, 4, NULL);
    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614F0F, newAddressPlus2, 4, NULL);
    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614F3A, newAddressPlus2, 4, NULL);
    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x614F65, newAddressPlus2, 4, NULL);
}
