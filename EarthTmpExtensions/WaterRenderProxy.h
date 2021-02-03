#pragma once
#include "pch.h"

class WaterRenderProxy
{
public:
	HRESULT SetWaterGreenOverlayTexture(LPVOID textureAddress, DWORD textureNum, DWORD textureUnknownValue);
	HRESULT RegisterWaterGreenOverlayTriangleRendering(D3DVERTEX* lpvVertices);

	HRESULT SetWaterTexture(DWORD textureNum, DWORD textureUnknownValue);
	HRESULT RegisterWaterTriangleRendering(D3DVERTEX* lpvVertices);

	/// <summary>
	/// Pushes to renderer all changes registered in current frame
	/// </summary>
	/// <param name="d3dDevice3"></param>
	/// <returns></returns>
	HRESULT CommitWater();
};
