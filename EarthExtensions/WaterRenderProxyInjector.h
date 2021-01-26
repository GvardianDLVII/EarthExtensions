#pragma once

#include "pch.h"
#include "WaterRenderProxy.h"

class WaterRenderProxyInjector
{
private:
	static bool WaterRenderContext;
	static WaterRenderProxy* WaterRenderer;
	LPVOID SetWaterTextureAddress;
	LPVOID RegisterWaterTriangleRenderingAddress;
	static HRESULT __stdcall SetWaterTextureWrapper(LPVOID textureAddress, DWORD textureNum, DWORD textureUnknownValue);
	static HRESULT __stdcall RegisterWaterTriangleRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _flags);
	void HookSetWaterTextureCall();
	void HookRegisterWaterTriangleRenderCall();
public:
	void SetWaterRenderContext(bool ctx);
	WaterRenderProxyInjector(WaterRenderProxy* waterRenderer);
	void Inject();
};