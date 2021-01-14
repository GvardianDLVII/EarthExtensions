#include "pch.h"
#include "TerrainRenderProxy.h"
#include "TerrainRenderProxyInjector.h"
#include "Utils.h"

HRESULT TerrainRenderProxyInjector::RegisterResourceSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	return proxy->RegisterResourceSquareRendering(lpvVertices, lpwIndices);
}
void TerrainRenderProxyInjector::HookSetResourceSquareTextureCall()
{
	const ULONG_PTR injectAddress = 0x005C9939;
	byte replacement[] = {
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 //erase
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, replacement, sizeof(replacement), NULL);
}
void TerrainRenderProxyInjector::HookRegisterResourceSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005C9B62;
	void** proxyFunctionAddress = &RegisterResourceSquareRenderingAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x52,                                                   //push edx
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
}