#pragma once

#include "pch.h"
#include "UnitShadowRenderProxy.h"

class ShadowRenderProxyInjector
{
private:
	static bool ShadowRenderContext;
	static UnitShadowRenderProxy* proxy;
	LPVOID SetUnitShadowTextureAddress;
	LPVOID RegisterUnitShadowSquareRenderingAddress;
	LPVOID CommitUnitShadowAddress;
	static HRESULT __stdcall SetUnitShadowTextureWrapper(LPVOID textureAddress, DWORD textureNum);
	static HRESULT __stdcall RegisterUnitShadowSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall CommitUnitShadowWrapper();
	void HookSetUnitShadowTextureCall();
	void HookRegisterUnitShadowSquareRenderCall();
	void HookCommitUnitShadowCall();
public:
	void SetShadowRenderContext(bool ctx);
	ShadowRenderProxyInjector();
	void Inject();
	~ShadowRenderProxyInjector();
};