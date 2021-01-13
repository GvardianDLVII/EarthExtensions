#include "pch.h"
#include "TerrainRenderProxy.h"
#include "TerrainRenderProxyInjector.h"

TerrainRenderProxy* TerrainRenderProxyInjector::proxy = 0;

HRESULT TerrainRenderProxyInjector::DoSomethingWithTextureWrapper(DWORD textureNum, DWORD textureSize)
{
	return proxy->DoSomethingWithTexture(textureNum, textureSize);
}
HRESULT TerrainRenderProxyInjector::RegisterSingleSquareRenderingAddressWrapper(LPVOID lpvVertices, LPWORD lpwIndices)
{
	return proxy->RegisterSingleSquareRendering(lpvVertices, lpwIndices);
}
HRESULT TerrainRenderProxyInjector::CommitWrapper()
{
	return proxy->Commit();
}
void TerrainRenderProxyInjector::HookTextureCall()
{
	const ULONG_PTR injectAddress = 0x005C8C3A;
	void** proxyFunctionAddress = &DoSomethingWithTextureAddress;
	byte* bytes = ToByteArray(proxyFunctionAddress);
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
	delete bytes;
}
void TerrainRenderProxyInjector::HookSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005C8F41;
	void** proxyFunctionAddress = &RegisterSingleSquareRenderingAddress;
	byte* bytes = ToByteArray(proxyFunctionAddress);
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
	delete bytes;
}
void TerrainRenderProxyInjector::HookCommitCall()
{
	const ULONG_PTR injectAddress = 0x005C9BCB;
	void** proxyFunctionAddress = &CommitAddress;
	byte* bytes = ToByteArray(proxyFunctionAddress);
	byte proxyCall[] = {
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
	delete bytes;
}
byte* TerrainRenderProxyInjector::ToByteArray(void** address)
{
	byte* bytes = new byte[4];
	bytes[0] = (int)(((ULONG)address >> 24) & 0xFF);
	bytes[1] = (int)(((ULONG)address >> 16) & 0xFF);
	bytes[2] = (int)(((ULONG)address >> 8) & 0XFF);
	bytes[3] = (int)((ULONG)address & 0XFF);
	return bytes;
}

TerrainRenderProxyInjector::TerrainRenderProxyInjector()
{
	proxy = new TerrainRenderProxy();
	DoSomethingWithTextureAddress = (LPVOID)((ULONG_PTR)DoSomethingWithTextureWrapper);
	RegisterSingleSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterSingleSquareRenderingAddressWrapper);
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