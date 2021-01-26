#include "pch.h"
#include "TerrainRenderProxy.h"
#include "TerrainRenderProxyInjector.h"

TerrainRenderProxy* TerrainRenderProxyInjector::proxy = 0;

HRESULT __stdcall TerrainRenderProxyInjector::CommitWrapper()
{
	return proxy->Commit();
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

void TerrainRenderProxyInjector::RemoveRedundantCode()
{
	//Resource draw begin call
	const ULONG_PTR injectAddress2 = 0x005C9931;
	byte replacement[] = {
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 //erase
	};

	//Resource draw end call
	const ULONG_PTR injectAddress = 0x005C9B96;
	byte replacement2[] = {
		0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 //erase
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, replacement, sizeof(replacement), NULL);
	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress2, replacement2, sizeof(replacement2), NULL);
}

TerrainRenderProxyInjector::TerrainRenderProxyInjector()
{
	proxy = new TerrainRenderProxy();
	SetGroundTextureAddress = (LPVOID)((ULONG_PTR)SetGroundTextureWrapper);
	RegisterGroundSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterGroundSquareRenderingWrapper);
	SetNavMeshTextureAddress = (LPVOID)((ULONG_PTR)SetNavMeshTextureWrapper);
	RegisterNavMeshSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterNavMeshSquareRenderingWrapper);
	SetGreenTextureAddress = (LPVOID)((ULONG_PTR)SetGreenTextureWrapper);
	RegisterGreenSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterGreenSquareRenderingWrapper);
	RegisterResourceSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterResourceSquareRenderingWrapper);
	CommitAddress = (LPVOID)((ULONG_PTR)CommitWrapper);
}
void TerrainRenderProxyInjector::Inject()
{
	HookSetGroundTextureCall();
	HookRegisterGroundSquareRenderCall();
	HookSetNavMeshTextureCall();
	HookRegisterNavMeshSquareRenderCall();
	HookSetGreenTextureCall();
	HookRegisterGreenSquareRenderCall();
	HookSetResourceTextureCall();
	HookRegisterResourceSquareRenderCall();
	HookCommitCall();
	RemoveRedundantCode();
}
TerrainRenderProxyInjector::~TerrainRenderProxyInjector()
{
	delete proxy;
}