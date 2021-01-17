#pragma once

#include "pch.h"
#include "UnitShadowRenderProxy.h"

class ShadowRenderProxyInjector
{
private:
	static UnitShadowRenderProxy* proxy;
	LPVOID SetUnitShadowSquareTextureAddress;
	LPVOID RegisterUnitShadowSquareRenderingAddress;
	LPVOID CommitUnitShadowAddress;
	static HRESULT __stdcall SetUnitShadowSquareTextureWrapper(LPVOID textureAddress, DWORD textureNum);
	static HRESULT __stdcall RegisterUnitShadowSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall CommitUnitShadowWrapper();
	void HookSetUnitShadowSquareTextureCall();
	void HookRegisterUnitShadowSquareRenderCall();
	void HookCommitUnitShadowCall();
public:
	ShadowRenderProxyInjector();
	void Inject();
	~ShadowRenderProxyInjector();
};