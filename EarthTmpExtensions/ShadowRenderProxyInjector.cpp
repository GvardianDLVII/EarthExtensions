#include "pch.h"
#include "ShadowRenderProxyInjector.h"
#include "OriginalMethods.h"

UnitShadowRenderProxy* ShadowRenderProxyInjector::proxy = 0;
bool ShadowRenderProxyInjector::ShadowRenderContext = false;

HRESULT __stdcall ShadowRenderProxyInjector::SetUnitShadowTextureWrapper(LPVOID textureAddress, DWORD textureNum)
{
	if (ShadowRenderContext)
	{
		return proxy->SetUnitShadowTexture(textureAddress, textureNum);
	}
	else
	{
		TmpSetTextureCall(textureAddress, textureNum, 4096);
		return 0;
	}
}
HRESULT __stdcall ShadowRenderProxyInjector::RegisterUnitShadowSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags)
{
	if (ShadowRenderContext)
	{
		return proxy->RegisterUnitShadowSquareRendering(lpvVertices, lpwIndices);
	}
	else
	{
		return GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, lpvVertices, 4, lpwIndices, 6, 0);
	}
}
HRESULT __stdcall ShadowRenderProxyInjector::CommitUnitShadowWrapper()
{
	return proxy->CommitUnitShadow();
}
void ShadowRenderProxyInjector::HookSetUnitShadowTextureCall()
{
	const ULONG_PTR injectAddress = 0x005DCF33;
	void** proxyFunctionAddress = &SetUnitShadowTextureAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x51,                                                   //push ecx
		0x8B, 0x0D, 0x24, 0xCA, 0x9F, 0x00,						//mov ecx, [009FCA24]
		0x51,                                                   //push ecx
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);

	const ULONG_PTR injectAddress2 = 0x005DC735;
	byte proxyCall2[] = {
		0x8B, 0x50, 0x04,										//mov edx, [eax+04h]
		0x42,													//inc edx
		0x89, 0x50, 0x04,										//mov [eax+04h], edx
		0x56,													//push esi
		0x50,													//push eax
		0x6A, 0x00,												//push 00
		0x8B, 0xBE, 0x70, 0x03, 0x00, 0x00,						//mov edi [esi+370h]
		0x57,                                                   //push edi
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x58,                                                   //pop eax
		0x5E,                                                   //pop esi
		0x90                                                    //nop
	};
	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress2, proxyCall2, sizeof(proxyCall2), NULL);
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
void ShadowRenderProxyInjector::HookCommitUnitShadowCall()
{
	const ULONG_PTR injectAddress = 0x005CB33C;
	void** proxyFunctionAddress = &CommitUnitShadowAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

void ShadowRenderProxyInjector::SetShadowRenderContext(bool ctx)
{
	ShadowRenderContext = ctx;
}

ShadowRenderProxyInjector::ShadowRenderProxyInjector()
{
	proxy = new UnitShadowRenderProxy();
	SetUnitShadowTextureAddress = (LPVOID)((ULONG_PTR)SetUnitShadowTextureWrapper);
	RegisterUnitShadowSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterUnitShadowSquareRenderingWrapper);
	CommitUnitShadowAddress = (LPVOID)((ULONG_PTR)CommitUnitShadowWrapper);
}
void ShadowRenderProxyInjector::Inject()
{
	HookSetUnitShadowTextureCall();
	HookRegisterUnitShadowSquareRenderCall();
	HookCommitUnitShadowCall();
}
ShadowRenderProxyInjector::~ShadowRenderProxyInjector()
{
	delete proxy;
}