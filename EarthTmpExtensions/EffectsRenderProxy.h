#pragma once
#include "pch.h"

class EffectsRenderProxy
{
public:
	HRESULT SetEffectsTexture(LPVOID textureAddress);
	HRESULT RegisterEffectsTriangleRendering(D3DVERTEX* lpvVertices);

	/// <summary>
	/// Pushes to renderer all changes registered in current frame
	/// </summary>
	/// <param name="d3dDevice3"></param>
	/// <returns></returns>
	HRESULT CommitEffects();
};
