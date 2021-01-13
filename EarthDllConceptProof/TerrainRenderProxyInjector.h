#pragma once

#include "pch.h"
#include "TerrainRenderProxy.h"

class TerrainRenderProxyInjector
{
private:
	static TerrainRenderProxy* proxy;
	LPVOID DoSomethingWithTextureAddress;
	LPVOID RegisterSingleSquareRenderingAddress;
	LPVOID CommitAddress;
	static HRESULT DoSomethingWithTextureWrapper(DWORD textureNum, DWORD textureSize);
	static HRESULT RegisterSingleSquareRenderingAddressWrapper(LPVOID lpvVertices, LPWORD lpwIndices);
	static HRESULT CommitWrapper();
	void HookTextureCall();
	void HookSquareRenderCall();
	void HookCommitCall();
	byte* ToByteArray(void** address);
public:
	TerrainRenderProxyInjector();
	void Inject();
	~TerrainRenderProxyInjector();
};