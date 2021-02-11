#include "pch.h"
#include "EffectsRenderProxyInjector.h"
#include "RenderManager.h"


HRESULT __stdcall EffectsRenderProxyInjector::SetEffectsTextureWrapper(LPVOID textureAddress)
{
	if (RenderManager::GetRenderingContext() == RenderingContextType::MeshesAndEffects)
	{
		return RenderManager::GetEffectsRenderer()->SetEffectsTexture(textureAddress);
	}
	else
	{
		TmpSetTextureCall(&textureAddress, 0, 4096);
		return 0;
	}
}
void EffectsRenderProxyInjector::HookSetEffectsTextureCall()
{
	const ULONG_PTR injectAddress = 0x005CE0A5;
	void** proxyFunctionAddress = &SetEffectsTextureAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x51,													//push ecx
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],		//call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

EffectsRenderProxyInjector::EffectsRenderProxyInjector()
{
	SetEffectsTextureAddress = (LPVOID)((ULONG_PTR)SetEffectsTextureWrapper);
}
void EffectsRenderProxyInjector::Inject()
{
	HookSetEffectsTextureCall();
}
