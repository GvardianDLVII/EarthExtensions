#pragma once

#include "pch.h"
#include "ShadowRenderProxy.h"

class ShadowRenderProxyInjector
{
private:
	static ShadowRenderProxy* proxy;
	LPVOID SetUnitShadowSquareTextureAddress;
	LPVOID RegisterUnitShadowSquareRenderingAddress;
	LPVOID CommitUnitShadowAddress;
	static HRESULT __stdcall SetUnitShadowSquareTextureWrapper(LPVOID textureAddress, DWORD textureNum);
	static HRESULT __stdcall RegisterUnitShadowSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall CommitUnitShadowWrapper();
	void HookSetUnitShadowSquareTextureCall();
	void HookRegisterUnitShadowSquareRenderCall();
	void HookCommitUnitShadowCall();

	LPVOID SetBuildingShadowSquareTextureAddress;
	LPVOID RegisterBuildingShadowSquareRenderingAddress;
	LPVOID CommitBuildingShadowAddress;
	static HRESULT __stdcall SetBuildingShadowSquareTextureWrapper(long param0, long param1, long param2, long param3, long param4, long param5, long param6);
	static HRESULT __stdcall RegisterBuildingShadowSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags);
	static HRESULT __stdcall CommitBuildingShadowWrapper();
	void HookSetBuildingShadowSquareTextureCall();
	void HookRegisterBuildingShadowSquareRenderCall();
	void HookCommitBuildingShadowCall();
public:
	ShadowRenderProxyInjector();
	void Inject();
	~ShadowRenderProxyInjector();
};