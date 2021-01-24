#pragma once

#include "pch.h"
#include "MeshRenderProxy.h"

class MeshRenderProxyInjector
{
private:
	static MeshRenderProxy* meshRenderer;
	LPVOID RegisterMeshTriangleRenderingAddress;
	static HRESULT __stdcall RegisterMeshTriangleRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _vertCount, DWORD _flags);
	void HookRegisterMeshTriangleRenderCall();
public:
	MeshRenderProxyInjector(MeshRenderProxy* meshRenderer);
	void Inject();
};