#pragma once

#include "pch.h"
#include "WaterRenderProxy.h"

class WaterRenderProxyInjector
{
private:
	static WaterRenderProxy* waterRenderer;
	LPVOID RegisterWaterTriangleRenderingAddress;
	static HRESULT __stdcall RegisterWaterTriangleRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _flags);
	void HookRegisterWaterTriangleRenderCall();
public:
	WaterRenderProxyInjector(WaterRenderProxy* waterRenderer);
	void Inject();
};