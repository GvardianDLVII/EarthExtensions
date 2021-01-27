#include "pch.h"
#include "TitlebarFixes.h"

void TitlebarFixes::Apply()
{
	if (!Configuration::GetEnableTitlebarFix())
	{
		return;
	}

	byte replacement1[] = {
		0x00, 0x86
	};
	WriteProcessMemory(GetCurrentProcess(), (PVOID)0x40A5DB, replacement1, sizeof(replacement1), NULL);
	byte replacement2[] = {
		0xE9, 0x8C, 0xB0, 0x33, 0x00, 0x90, 0x90, 0x90
	};
	WriteProcessMemory(GetCurrentProcess(), (PVOID)0x40A5DF, replacement2, sizeof(replacement2), NULL);
	byte replacement3[] = {
		0x90, 0x90, 0x90, 0x90, 0x90
	};
	WriteProcessMemory(GetCurrentProcess(), (PVOID)0x40A6A5, replacement3, sizeof(replacement3), NULL);
	byte replacement4[] = {
		0x90, 0x90, 0x90, 0x90, 0x90
	};
	WriteProcessMemory(GetCurrentProcess(), (PVOID)0x40A7A4, replacement4, sizeof(replacement4), NULL);
	byte replacement5[] = {
		0x68, 0x00, 0x00, 0x04, 0x00, 0xFF, 0x15, 0xC8, 0x62, 0x74, 0x00, 0xE9, 0x67, 0x4F, 0xCC, 0xFF
	};
	WriteProcessMemory(GetCurrentProcess(), (PVOID)0x745670, replacement5, sizeof(replacement5), NULL);
}
