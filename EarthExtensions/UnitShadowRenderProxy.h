#pragma once
#include "pch.h"

class UnitShadowRenderProxy
{
private:
	IDirect3DDevice3* d3dDevice;
public:
	/// <summary>
	/// It replaces a single call to IDirect3DDevice::DrawIndexedPrimitive. The difference is, that it stacks the draw call in memory instead of calling renderer.
	/// The actual rendering is performed at the end, in Commit function
	/// </summary>
	/// <param name="lpvVertices"></param>
	/// <param name="lpwIndices"></param>
	/// <returns></returns>
	HRESULT RegisterUnitShadowSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices);

	/// <summary>
	/// Pushes to renderer all changes registered in current frame
	/// </summary>
	/// <param name="d3dDevice3"></param>
	/// <returns></returns>
	HRESULT CommitUnitShadow();
};
