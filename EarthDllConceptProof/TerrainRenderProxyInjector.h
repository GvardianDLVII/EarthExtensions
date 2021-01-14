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
	static HRESULT RegisterSquareTextureWrapper(DWORD textureNum, DWORD textureSize);
	static HRESULT RegisterSingleSquareRenderingAddressWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices);
	static HRESULT CommitWrapper();
	void HookTextureCall();
	void HookSquareRenderCall();
	void HookCommitCall();
public:
	TerrainRenderProxyInjector();
	void Inject();
	~TerrainRenderProxyInjector();
};