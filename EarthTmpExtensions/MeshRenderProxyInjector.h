#pragma once

#include "pch.h"
#include "MeshRenderProxy.h"

class MeshRenderProxyInjector
{
private:
	LPVOID SetMeshTextureAddress;
	LPVOID RegisterMeshTriangleRenderingAddress;
	static HRESULT __stdcall SetMeshTextureWrapper(LPVOID textureAddress, DWORD textureNum);
	static HRESULT __stdcall RegisterMeshTriangleRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _indCount, DWORD _flags);
	void HookSetMeshTextureCall();
	void HookRegisterMeshTriangleRenderCall();
public:
	MeshRenderProxyInjector();
	void Inject();
};
