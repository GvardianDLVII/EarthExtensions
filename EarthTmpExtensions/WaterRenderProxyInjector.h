#pragma once

#include "pch.h"
#include "WaterRenderProxy.h"

class WaterRenderProxyInjector
{
private:
	LPVOID SetWaterGreenOverlayTextureAddress;
	LPVOID RegisterWaterGreenOverlayTriangleRenderingAddress;
	LPVOID SetWaterTextureAddress;
	LPVOID RegisterWaterTriangleRenderingAddress;
	static HRESULT __stdcall SetWaterGreenOverlayTextureWrapper(LPVOID textureAddress, DWORD textureNum, DWORD textureUnknownValue);
	static HRESULT __stdcall RegisterWaterGreenOverlayTriangleRenderingWrapper(D3DVERTEX* lpvVertices);
	static HRESULT __stdcall SetWaterTextureWrapper(LPVOID textureAddress, DWORD textureNum, DWORD textureUnknownValue);
	static HRESULT __stdcall RegisterWaterTriangleRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _flags);
	void HookSetWaterGreenOverlayTextureCall();
	void HookRegisterWaterGreenOverlayTriangleRenderCall();
	void HookSetWaterTextureCall();
	void HookRegisterWaterTriangleRenderCall();
public:
	WaterRenderProxyInjector();
	void Inject();
};