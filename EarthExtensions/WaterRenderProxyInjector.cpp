#include "pch.h"
#include "WaterRenderProxyInjector.h"
#include "OriginalMethods.h"
#include "RenderManager.h"

WaterRenderProxy* WaterRenderProxyInjector::waterRenderer = 0;

HRESULT __stdcall WaterRenderProxyInjector::RegisterWaterSquareRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _flags)
{
	if (RenderManager::GetRenderingContext() == RenderingContextType::Water)
	{
		return waterRenderer->RegisterWaterSquareRendering(lpvVertices);
	}
	else //default render action
	{
		GetD3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, lpvVertices, 3, 0);
	}
}

WaterRenderProxyInjector::WaterRenderProxyInjector(WaterRenderProxy* waterRenderer)
{
	waterRenderer = waterRenderer;
	RegisterWaterSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterWaterSquareRenderingWrapper);
}

void WaterRenderProxyInjector::Inject()
{
	HookRegisterWaterSquareRenderCall();
}

void WaterRenderProxyInjector::HookRegisterWaterSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005C5299;
	void** proxyFunctionAddress = &RegisterWaterSquareRenderingAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x89, 0x4D, 0xD4,										//mov [ebp-2C],ecx
		0xD8, 0x05, 0x28, 0xBC, 0x9F, 0x00,						//fadd dword ptr [009FBC28]
		0xD9, 0x5D, 0xC4,										//fstp dword ptr [ebp-3C]
		0xD9, 0x05, 0xB4, 0x91, 0x74, 0x00,						//fld dword ptr [007491B4]
		0xD8, 0x75, 0xC4,										//fdiv dword ptr [ebp-3C]
		0xD9, 0x5D, 0xC8,										//fstp dword ptr [ebp-38]
		0x52,													//push edx
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],		//call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
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








