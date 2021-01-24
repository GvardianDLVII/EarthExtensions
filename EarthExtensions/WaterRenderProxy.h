#pragma once
#include "pch.h"

class WaterRenderProxy
{
public:
	/// <summary>
	/// It replaces a single call to IDirect3DDevice::DrawIndexedPrimitive. The difference is, that it stacks the draw call in memory instead of calling renderer.
	/// The actual rendering is performed at the end, in Commit function
	/// </summary>
	/// <param name="lpvVertices"></param>
	/// <param name="lpwIndices"></param>
	/// <returns></returns>
	HRESULT RegisterWaterTriangleRendering(D3DVERTEX* lpvVertices);

	/// <summary>
	/// Pushes to renderer all changes registered in current frame
	/// </summary>
	/// <param name="d3dDevice3"></param>
	/// <returns></returns>
	HRESULT CommitWater();
};
