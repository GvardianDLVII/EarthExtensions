#include "pch.h"
#include "WidescreenFixes.h"

void WidescreenFixes::ApplyConstructorCrashFix()
{
    byte replacement[] = {
        0xB8,
        0x82,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90
    };

    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x4FFE7A, replacement, sizeof(replacement), NULL);
}
void WidescreenFixes::AdjustSidepanelSize()
{
    int sidePanelFactor = Configuration::GetSidePanelWidthFactor();
    byte bytes[4];
    ToByteArray(sidePanelFactor, bytes);
    byte replacement[] = {
        0x8B,
        0x43,
        0x54,
        0x89,
        0x45,
        0x08,
        0xB8,
        bytes[3],
        bytes[2],
        bytes[1],
        bytes[0],
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90
    };

    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x66335C, replacement, sizeof(replacement), NULL);
}
void WidescreenFixes::AdjustBottomPanelSize()
{
    int bottomPanelFactor = Configuration::GetBottomPanelWidthFactor();
    byte bytes[4];
    ToByteArray(bottomPanelFactor, bytes);
    byte replacement[] = {
        0x8B,
        0x4F,
        0x0C,
        0xB8,
        bytes[3],
        bytes[2],
        bytes[1],
        bytes[0],
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90,
        0x90
    };

    WriteProcessMemory(GetCurrentProcess(), (PVOID)0x66346E, replacement, sizeof(replacement), NULL);
}
void WidescreenFixes::Apply()
{
    if (Configuration::GetEnableConstructorF1CrashFix())
    {
        ApplyConstructorCrashFix();
    }
    if (Configuration::GetOverrideSidePanelWidthFactor())
    {
        AdjustSidepanelSize();
    }
    if (Configuration::GetOverrideBottomPanelWidthFactor())
    {
        AdjustBottomPanelSize();
    }
}