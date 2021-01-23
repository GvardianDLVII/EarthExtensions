#pragma once

#include "pch.h"
#include "WaterRenderProxy.h"

class WaterRenderProxyInjector
{
private:
	static WaterRenderProxy* waterRenderer;
	LPVOID RegisterWaterSquareRenderingAddress;
	static HRESULT __stdcall RegisterWaterSquareRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _flags);
	void HookRegisterWaterSquareRenderCall();
public:
	WaterRenderProxyInjector(WaterRenderProxy* waterRenderer);
	void Inject();
};