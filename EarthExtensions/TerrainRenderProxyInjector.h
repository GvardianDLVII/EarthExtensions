#pragma once

#include "pch.h"
#include "TerrainRenderProxy.h"

class TerrainRenderProxyInjector
{
private:
	static TerrainRenderProxy* proxy;
	LPVOID SetGroundTextureAddress;
	LPVOID RegisterGroundSquareRenderingAddress;
	LPVOID RegisterResourceSquareRenderingAddress;
	LPVOID SetNavMeshTextureAddress;
	LPVOID RegisterNavMeshSquareRenderingAddress;
	LPVOID SetGreenTextureAddress;
	LPVOID RegisterGreenSquareRenderingAddress;
	LPVOID CommitAddress;
	static HRESULT __stdcall SetGroundTextureWrapper(DWORD textureNum, DWORD textureSize);
	static HRESULT __stdcall RegisterGroundSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall RegisterResourceSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall SetNavMeshTextureWrapper(DWORD textureNum);
	static HRESULT __stdcall RegisterNavMeshSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall SetGreenTextureWrapper(DWORD textureNum, DWORD textureSize);
	static HRESULT __stdcall RegisterGreenSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall CommitWrapper();
	void HookSetGroundTextureCall();
	void HookRegisterGroundSquareRenderCall();
	void HookSetResourceTextureCall();
	void HookRegisterResourceSquareRenderCall();
	void HookSetNavMeshTextureCall();
	void HookRegisterNavMeshSquareRenderCall();
	void HookSetGreenTextureCall();
	void HookRegisterGreenSquareRenderCall();
	void HookCommitCall();
	void RemoveRedundantCode();
public:
	TerrainRenderProxyInjector();
	void Inject();
	~TerrainRenderProxyInjector();
};