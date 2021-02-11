#pragma once

#include "pch.h"
#include "MeshRenderProxy.h"

class EffectsRenderProxyInjector
{
private:
	LPVOID SetEffectsTextureAddress;
	static HRESULT __stdcall SetEffectsTextureWrapper(LPVOID textureAddress);
	void HookSetEffectsTextureCall();
public:
	EffectsRenderProxyInjector();
	void Inject();
};
