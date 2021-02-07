#include "pch.h"
#include "WaterRenderProxyInjector.h"
#include "OriginalMethods.h"

WaterRenderProxy* WaterRenderProxyInjector::WaterRenderer = 0;
bool WaterRenderProxyInjector::WaterRenderContext = false;

HRESULT __stdcall WaterRenderProxyInjector::SetWaterTextureWrapper(LPVOID textureAddress, DWORD textureNum, DWORD textureUnknowValue)
{
	if (WaterRenderContext)
	{
		return WaterRenderer->SetWaterTexture(textureNum, textureUnknowValue);
	}
	else
	{
		TmpSetTextureCall(textureAddress, textureNum, textureUnknowValue);
		return 0;
	}
}
HRESULT __stdcall WaterRenderProxyInjector::RegisterWaterTriangleRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _flags)
{
	if (WaterRenderContext)
	{
		return WaterRenderer->RegisterWaterTriangleRendering(lpvVertices);
	}
	else //default render action
	{
		return GetD3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, lpvVertices, 3, 0);
	}
}
HRESULT __stdcall WaterRenderProxyInjector::SetWaterGreenOverlayTextureWrapper(LPVOID textureAddress, DWORD textureNum, DWORD textureUnknowValue)
{
	if (WaterRenderContext)
	{
		return WaterRenderer->SetWaterGreenOverlayTexture(textureAddress, textureNum, textureUnknowValue);
	}
	else
	{
		TmpSetTextureCall(textureAddress, textureNum, textureUnknowValue);
		return 0;
	}
}
HRESULT __stdcall WaterRenderProxyInjector::RegisterWaterGreenOverlayTriangleRenderingWrapper(D3DVERTEX* lpvVertices)
{
	if (WaterRenderContext)
	{
		return WaterRenderer->RegisterWaterGreenOverlayTriangleRendering(lpvVertices);
	}
	else //default render action
	{
		return GetD3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, lpvVertices, 3, 0);
	}
}
void WaterRenderProxyInjector::SetWaterRenderContext(bool ctx)
{
	WaterRenderContext = ctx;
}
void WaterRenderProxyInjector::HookSetWaterTextureCall()
{
	const ULONG_PTR injectAddress = 0x0061EBEF;
	void** proxyFunctionAddress = &SetWaterTextureAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x68, 0x4C, 0x15, 0xA4, 0x00,							//push 0x00A4154C
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0]      //call DWRD PTR ds:${proxyAddress}
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}
void WaterRenderProxyInjector::HookRegisterWaterTriangleRenderCall()
{
	const ULONG_PTR injectAddress = 0x005C5299;
	void** proxyFunctionAddress = &RegisterWaterTriangleRenderingAddress;
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

static BYTE waterGreenOverlayProxyFunction[] =
{
	0x55,									//push	ebp
	0x89, 0xE5,								//mov	ebp, esp
	0x56,									//push	esi
	0x57,									//push	edi
	0xFF, 0x75, 0x0C,						//push  [ebp+0Ch]
	0xFF, 0x75, 0x08,						//push  [ebp+08h]
	0x51,									//push	ecx,
	0xFF, 0x15, 0x00, 0x00, 0x00, 0x00,		//call	[greenProxy]
	0x5F,									//pop	edi
	0x5E,									//pop	esi
	0x5D,									//pop	ebp
	0xC2, 0x08, 0x00						//ret 8
};

void WaterRenderProxyInjector::HookSetWaterGreenOverlayTextureCall()
{
	void** proxyFunctionAddress = &SetWaterGreenOverlayTextureAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	waterGreenOverlayProxyFunction[14] = bytes[3];
	waterGreenOverlayProxyFunction[15] = bytes[2];
	waterGreenOverlayProxyFunction[16] = bytes[1];
	waterGreenOverlayProxyFunction[17] = bytes[0];

	const ULONG_PTR injectAddress = 0x0061985A;
	ULONG relativeAddress = (ULONG)waterGreenOverlayProxyFunction - (ULONG)0x0061985F;
	byte bytes1[4];
	ToByteArray(relativeAddress, bytes1);
	byte proxyCall[] = {
		0xE8, bytes1[3], bytes1[2], bytes1[1], bytes1[0]     //call ${relativeAddress}
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
	byte txtSet1[] = {
		0xBB, 0x40, 0x15, 0xA4, 0x00,			//mov ebx, 00A41540
		0x90									//nop
	};
	WriteProcessMemory(GetCurrentProcess(), (PVOID)0x619807, txtSet1, sizeof(txtSet1), NULL);
	byte txtSet2[] = {
		0xB9, 0x2C, 0x15, 0xA4, 0x00,			//mov ecx, 00A4152C
		0x90									//nop
	};
	WriteProcessMemory(GetCurrentProcess(), (PVOID)0x619830, txtSet2, sizeof(txtSet2), NULL);
	byte txtSet3[] = {
		0xB9, 0x24, 0x15, 0xA4, 0x00,			//mov ecx, 00A41524
		0x90									//nop
	};
	WriteProcessMemory(GetCurrentProcess(), (PVOID)0x61984A, txtSet3, sizeof(txtSet3), NULL);
	byte txtSet4[] = {
		0xB9, 0x28, 0x15, 0xA4, 0x00,			//mov ecx, 00A41528
		0x90									//nop
	};
	WriteProcessMemory(GetCurrentProcess(), (PVOID)0x619854, txtSet4, sizeof(txtSet4), NULL);

	const ULONG_PTR injectAddress2 = 0x0061F9A2;
	void** proxyFunctionAddress2 = &SetWaterGreenOverlayTextureAddress;
	byte bytes2[4];
	ToByteArray((ULONG)proxyFunctionAddress2, bytes2);
	byte proxyCall2[] = {
		0x68, 0x20, 0x15, 0xA4, 0x00,								//push 0x00A41520
		0xFF, 0x15, bytes2[3], bytes2[2], bytes2[1], bytes2[0]      //call DWRD PTR ds:${proxyAddress}
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress2, proxyCall2, sizeof(proxyCall2), NULL);

	const ULONG_PTR injectAddress3 = 0x0061F614;
	void** proxyFunctionAddress3 = &SetWaterGreenOverlayTextureAddress;
	byte bytes3[4];
	ToByteArray((ULONG)proxyFunctionAddress3, bytes3);
	byte proxyCall3[] = {
		0x68, 0x44, 0x15, 0xA4, 0x00,								//push 0x00A41544
		0xFF, 0x15, bytes3[3], bytes3[2], bytes3[1], bytes3[0]      //call DWRD PTR ds:${proxyAddress}
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress3, proxyCall3, sizeof(proxyCall3), NULL);
}
void WaterRenderProxyInjector::HookRegisterWaterGreenOverlayTriangleRenderCall()
{
	const ULONG_PTR injectAddress = 0x005C43C5;
	void** proxyFunctionAddress = &RegisterWaterGreenOverlayTriangleRenderingAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0xD8, 0x05, 0x28, 0xBC, 0x9F, 0x00,						//fadd dword ptr[009FBC28]
		0xD9, 0x5D, 0xC4,										//fstp dword ptr[ebp - 3C]
		0xD9, 0x05, 0xB4, 0x91, 0x74, 0x00,						//fld dword ptr[007491B4]
		0xD8, 0x75, 0xC4,										//fdiv dword ptr[ebp - 3C]
		0xD9, 0x5D, 0xC8,										//fstp dword ptr[ebp - 38]
		0x8D, 0x4D, 0x9C,										//lea ecx,[ebp - 64]
		0x51,													//push ecx
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],		//call DWRD PTR ds:${proxyAddress}
		0x90,
		0x90,
		0x90,
		0x90,
		0x90,
		0x90,
		0x90,
		0x90,
		0x90,
		0x90,
		0x90
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

WaterRenderProxyInjector::WaterRenderProxyInjector(WaterRenderProxy* waterRenderer)
{
	WaterRenderer = waterRenderer;
	SetWaterTextureAddress = (LPVOID)((ULONG_PTR)SetWaterTextureWrapper);
	RegisterWaterTriangleRenderingAddress = (LPVOID)((ULONG_PTR)RegisterWaterTriangleRenderingWrapper);
	SetWaterGreenOverlayTextureAddress = (LPVOID)((ULONG_PTR)SetWaterGreenOverlayTextureWrapper);
	RegisterWaterGreenOverlayTriangleRenderingAddress = (LPVOID)((ULONG_PTR)RegisterWaterGreenOverlayTriangleRenderingWrapper);
}
void WaterRenderProxyInjector::Inject()
{
	HookSetWaterTextureCall();
	HookRegisterWaterTriangleRenderCall();
	if (Configuration::GetEnableWaterGreenOverlayRenderingOptimization())
	{
		HookSetWaterGreenOverlayTextureCall();
		HookRegisterWaterGreenOverlayTriangleRenderCall();
	}
}
