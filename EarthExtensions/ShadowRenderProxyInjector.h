#pragma once

#include "pch.h"
#include "UnitShadowRenderProxy.h"

class ShadowRenderProxyInjector
{
private:
	static UnitShadowRenderProxy* unitShadowRenderer;
	LPVOID RegisterUnitShadowSquareRenderingAddress;
	static HRESULT __stdcall RegisterUnitShadowSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	void HookRegisterUnitShadowSquareRenderCall();

	void HookRegisterBuildingShadowSquareRenderCall();
public:
	ShadowRenderProxyInjector(UnitShadowRenderProxy* waterRenderer);
	void Inject();
};