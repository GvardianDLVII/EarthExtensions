#include "pch.h"
#include "TerrainRenderProxyInjector.h"

HRESULT __stdcall TerrainRenderProxyInjector::SetGreenTextureWrapper(DWORD textureNum, DWORD textureSize)
{
	return proxy->SetGreenTexture(textureNum, textureSize);
}
HRESULT __stdcall TerrainRenderProxyInjector::RegisterGreenSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags)
{
	return proxy->RegisterGreenSquareRendering(lpvVertices, lpwIndices);
}
void TerrainRenderProxyInjector::HookSetGreenTextureCall()
{
	const ULONG_PTR injectAddress = 0x005CC3B2;
	void** proxyFunctionAddress = &SetGreenTextureAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x52,                                                   //push edx
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}
void TerrainRenderProxyInjector::HookRegisterGreenSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005CC3F9;
	const ULONG_PTR injectAddress2 = 0x005CC410;
	void** proxyFunctionAddress = &RegisterGreenSquareRenderingAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x56,                                                   //push esi
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress2, proxyCall, sizeof(proxyCall), NULL);
}