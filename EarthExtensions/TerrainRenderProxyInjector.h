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
	LPVOID SetNavMeshSquareTextureAddress;
	LPVOID RegisterNavMeshSquareRenderingAddress;
	LPVOID SetGreenSquareTextureAddress;
	LPVOID RegisterGreenSquareRenderingAddress;
	LPVOID CommitAddress;
	static HRESULT __stdcall SetGroundSquareTextureWrapper(DWORD textureNum, DWORD textureSize);
	static HRESULT __stdcall RegisterGroundSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall RegisterResourceSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall SetNavMeshSquareTextureWrapper(DWORD textureNum);
	static HRESULT __stdcall RegisterNavMeshSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall SetGreenSquareTextureWrapper(DWORD textureNum, DWORD textureSize);
	static HRESULT __stdcall RegisterGreenSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall CommitWrapper();
	void HookSetGroundSquareTextureCall();
	void HookRegisterGroundSquareRenderCall();
	void HookSetResourceSquareTextureCall();
	void HookRegisterResourceSquareRenderCall();
	void HookSetNavMeshSquareTextureCall();
	void HookRegisterNavMeshSquareRenderCall();
	void HookSetGreenSquareTextureCall();
	void HookRegisterGreenSquareRenderCall();
	void HookCommitCall();
	void RemoveRedundantCode();
public:
	TerrainRenderProxyInjector();
	void Inject();
	~TerrainRenderProxyInjector();
};