#pragma once
#include "pch.h"
#include "GroundRenderCallGroup.h"
#include "NavMeshRenderCallGroup.h"
#include "GreenOverlayRenderCallGroup.h"
#include "ResourceRenderCallGroup.h"

class TerrainRenderProxy
{
protected:
	GroundRenderCallGroup* groundCalls[1024];
	NavMeshRenderCallGroup* navMeshCalls[1024];
	GreenOverlayRenderCallGroup* greenCalls[1024];
	ResourceRenderCallGroup* resourceRenderCall;
public:
	TerrainRenderProxy();
	~TerrainRenderProxy();

	HRESULT SetGroundTexture(DWORD textureNum, DWORD textureSize);
	HRESULT RegisterGroundSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices);
	HRESULT SetNavMeshTexture(DWORD textureNum);
	HRESULT RegisterNavMeshSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices);
	HRESULT SetGreenTexture(DWORD textureNum, DWORD textureSize);
	HRESULT RegisterGreenSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices);
	HRESULT RegisterResourceSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices);

	/// <summary>
	/// Pushes to renderer all changes registered in current frame
	/// </summary>
	/// <param name="d3dDevice3"></param>
	/// <returns></returns>
	HRESULT Commit();

};