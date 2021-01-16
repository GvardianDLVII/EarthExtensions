#include "pch.h"
#include "TerrainRenderProxy.h"
#include "TerrainRenderProxyInjector.h"
#include "Utils.h"

HRESULT __stdcall TerrainRenderProxyInjector::SetNavMeshSquareTextureWrapper(DWORD textureNum)
{
	return proxy->SetNavMeshSquareTexture(textureNum);
}
HRESULT __stdcall TerrainRenderProxyInjector::RegisterNavMeshSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags)
{
	return proxy->RegisterNavMeshSquareRendering(lpvVertices, lpwIndices);
}
void TerrainRenderProxyInjector::HookSetNavMeshSquareTextureCall()
{
	const ULONG_PTR injectAddress = 0x005CC10A;
	void** proxyFunctionAddress = &SetNavMeshSquareTextureAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x50,                                                   //push eax
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
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
void TerrainRenderProxyInjector::HookRegisterNavMeshSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005CC17D;
	const ULONG_PTR injectAddress2 = 0x005CC194;
	void** proxyFunctionAddress = &RegisterNavMeshSquareRenderingAddress;
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