#include "pch.h"
#include "TerrainRenderProxy.h"
#include "TerrainRenderProxyInjector.h"
#include "Utils.h"

HRESULT __stdcall TerrainRenderProxyInjector::SetGroundSquareTextureWrapper(DWORD textureNum, DWORD textureSize)
{
	return proxy->SetGroundSquareTexture(textureNum, textureSize);
}
HRESULT __stdcall TerrainRenderProxyInjector::RegisterGroundSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags)
{
	return proxy->RegisterGroundSquareRendering(lpvVertices, lpwIndices);
}
void TerrainRenderProxyInjector::HookSetGroundSquareTextureCall()
{
	const ULONG_PTR injectAddress = 0x005C8C3A;
	void** proxyFunctionAddress = &SetGroundSquareTextureAddress;
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
void TerrainRenderProxyInjector::HookRegisterGroundSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005C8F41;
	void** proxyFunctionAddress = &RegisterGroundSquareRenderingAddress;
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