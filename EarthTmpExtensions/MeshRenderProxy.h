#pragma once
#include "pch.h"

class MeshRenderProxy
{
public:
	HRESULT SetMeshTexture(LPVOID textureAddress, DWORD textureNum);
	HRESULT RegisterMeshTriangleRendering(D3DVERTEX* lpvVertices);

	/// <summary>
	/// Pushes to renderer all changes registered in current frame
	/// </summary>
	/// <param name="d3dDevice3"></param>
	/// <returns></returns>
	HRESULT CommitMesh();
};
