#include "pch.h"
#include "ShadowRenderProxyInjector.h"
#include "RenderManager.h"
#include "OriginalMethods.h"

UnitShadowRenderProxy* ShadowRenderProxyInjector::unitShadowRenderer = 0;

HRESULT __stdcall ShadowRenderProxyInjector::RegisterUnitShadowSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags)
{
	if (RenderManager::GetRenderingContext() == RenderingContextType::UnitShadows)
	{
		return unitShadowRenderer->RegisterUnitShadowSquareRendering(lpvVertices, lpwIndices);
	}
	else //default render action
	{
		GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, lpvVertices, 4, lpwIndices, 6, 0);
	}
}
void ShadowRenderProxyInjector::HookRegisterBuildingShadowSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005CAC00;
	void** proxyFunctionAddress = &RegisterUnitShadowSquareRenderingAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x51,                                                   //push ecx
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}
void ShadowRenderProxyInjector::HookRegisterUnitShadowSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005CB2C9;
	void** proxyFunctionAddress = &RegisterUnitShadowSquareRenderingAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x52,                                                   //push edx
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

ShadowRenderProxyInjector::ShadowRenderProxyInjector(UnitShadowRenderProxy* proxy)
{
	unitShadowRenderer = proxy;
	RegisterUnitShadowSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterUnitShadowSquareRenderingWrapper);
}
void ShadowRenderProxyInjector::Inject()
{
	HookRegisterUnitShadowSquareRenderCall();
	//HookRegisterBuildingShadowSquareRenderCall();
}
