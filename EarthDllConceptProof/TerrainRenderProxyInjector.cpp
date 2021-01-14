#include "pch.h"
#include "TerrainRenderProxy.h"
#include "TerrainRenderProxyInjector.h"
#include "Utils.h"

TerrainRenderProxy* TerrainRenderProxyInjector::proxy = 0;

HRESULT TerrainRenderProxyInjector::SetGroundSquareTextureWrapper(DWORD textureNum, DWORD textureSize)
{
	return proxy->SetGroundSquareTexture(textureNum, textureSize);
}
HRESULT TerrainRenderProxyInjector::RegisterGroundSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	return proxy->RegisterGroundSquareRendering(lpvVertices, lpwIndices);
}
HRESULT TerrainRenderProxyInjector::CommitWrapper()
{
	return proxy->Commit();
}
void TerrainRenderProxyInjector::HookTextureCall()
{
	const ULONG_PTR injectAddress = 0x005C8C3A;
	void** proxyFunctionAddress = &DoSomethingWithTextureAddress;
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
void TerrainRenderProxyInjector::HookSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005C8F41;
	void** proxyFunctionAddress = &RegisterSingleSquareRenderingAddress;
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
void TerrainRenderProxyInjector::HookCommitCall()
{
	const ULONG_PTR injectAddress = 0x005C9BCB;
	void** proxyFunctionAddress = &CommitAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

TerrainRenderProxyInjector::TerrainRenderProxyInjector()
{
	proxy = new TerrainRenderProxy();
	DoSomethingWithTextureAddress = (LPVOID)((ULONG_PTR)SetGroundSquareTextureWrapper);
	RegisterSingleSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterGroundSquareRenderingWrapper);
	CommitAddress = (LPVOID)((ULONG_PTR)CommitWrapper);
}
void TerrainRenderProxyInjector::Inject()
{
	HookTextureCall();
	HookSquareRenderCall();
	HookCommitCall();
}
TerrainRenderProxyInjector::~TerrainRenderProxyInjector()
{
	delete proxy;
}