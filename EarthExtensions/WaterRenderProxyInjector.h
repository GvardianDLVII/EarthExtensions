#pragma once

#include "pch.h"
#include "WaterRenderProxy.h"

class WaterRenderProxyInjector
{
private:
	static bool WaterRenderContext;
	static WaterRenderProxy* WaterRenderer;
	LPVOID SetWaterSquareTextureAddress;
	LPVOID RegisterWaterSquareRenderingAddress;
	static HRESULT __stdcall SetWaterSquareTextureWrapper(LPVOID textureAddress, DWORD textureNum, DWORD textureUnknownValue);
	static HRESULT __stdcall RegisterWaterSquareRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _flags);
	void HookSetWaterSquareTextureCall();
	void HookRegisterWaterSquareRenderCall();
public:
	void SetWaterRenderContext(bool ctx);
	WaterRenderProxyInjector(WaterRenderProxy* waterRenderer);
	void Inject();
};