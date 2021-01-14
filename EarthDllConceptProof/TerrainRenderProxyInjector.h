#pragma once

#include "pch.h"
#include "TerrainRenderProxy.h"

class TerrainRenderProxyInjector
{
private:
	static TerrainRenderProxy* proxy;
	LPVOID SetGroundSquareTextureAddress;
	LPVOID RegisterGroundSquareRenderingAddress;
	LPVOID RegisterResourceSquareRenderingAddress;
	LPVOID CommitAddress;
	static HRESULT SetGroundSquareTextureWrapper(DWORD textureNum, DWORD textureSize);
	static HRESULT RegisterGroundSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices);
	static HRESULT RegisterResourceSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices);
	static HRESULT CommitWrapper();
	void HookSetGroundSquareTextureCall();
	void HookRegisterGroundSquareRenderCall();
	void HookSetResourceSquareTextureCall();
	void HookRegisterResourceSquareRenderCall();
	void HookCommitCall();
public:
	TerrainRenderProxyInjector();
	void Inject();
	~TerrainRenderProxyInjector();
};