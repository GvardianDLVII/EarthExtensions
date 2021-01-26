#pragma once

#include "pch.h"
#include "MeshRenderProxy.h"

class MeshRenderProxyInjector
{
private:
	static bool meshRenderContext;
	static MeshRenderProxy* meshRenderer;
	LPVOID SetMeshSquareTextureAddress;
	LPVOID RegisterMeshSquareRenderingAddress;
	static HRESULT __stdcall SetMeshSquareTextureWrapper(LPVOID textureAddress, DWORD textureNum);
	static HRESULT __stdcall RegisterMeshSquareRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _indCount, DWORD _flags);
	void HookSetMeshSquareTextureCall();
	void HookRegisterMeshSquareRenderCall();
public:
	void SetMeshRenderContext(bool ctx);
	MeshRenderProxyInjector(MeshRenderProxy* meshRenderer);
	void Inject();
};
