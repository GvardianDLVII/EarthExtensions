#pragma once

#include "pch.h"
#include "UnitShadowRenderProxy.h"

class ShadowRenderProxyInjector
{
private:
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
	ShadowRenderProxyInjector();
	void Inject();
};