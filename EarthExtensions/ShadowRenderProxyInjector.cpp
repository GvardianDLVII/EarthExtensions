#include "pch.h"
#include "ShadowRenderProxyInjector.h"

ShadowRenderProxy* ShadowRenderProxyInjector::proxy = 0;

HRESULT __stdcall ShadowRenderProxyInjector::SetUnitShadowSquareTextureWrapper(LPVOID textureAddress, DWORD textureNum)
{
	return proxy->SetUnitShadowSquareTexture(textureAddress, textureNum);
}
HRESULT __stdcall ShadowRenderProxyInjector::RegisterUnitShadowSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags)
{
	return proxy->RegisterUnitShadowSquareRendering(lpvVertices, lpwIndices);
}
HRESULT __stdcall ShadowRenderProxyInjector::CommitUnitShadowWrapper()
{
	return proxy->CommitUnitShadow();
}
HRESULT __stdcall ShadowRenderProxyInjector::SetBuildingShadowSquareTextureWrapper(long param0, long param1, long param2, long param3, long param4, long param5, long param6)
{
	return proxy->SetBuildingShadowSquareTexture(param0, param1, param2, param3, param4, param5, param6);
}
HRESULT __stdcall ShadowRenderProxyInjector::RegisterBuildingShadowSquareRenderingWrapper(D3DVERTEX* lpvVertices, LPWORD lpwIndices, DWORD _indCount, DWORD _flags)
{
	return proxy->RegisterBuildingShadowSquareRendering(lpvVertices, lpwIndices);
}
HRESULT __stdcall ShadowRenderProxyInjector::CommitBuildingShadowWrapper()
{
	return proxy->CommitBuildingShadow();
}

void ShadowRenderProxyInjector::HookSetUnitShadowSquareTextureCall()
{
	const ULONG_PTR injectAddress = 0x005DCF33;
	void** proxyFunctionAddress = &SetUnitShadowSquareTextureAddress;
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

void ShadowRenderProxyInjector::HookSetBuildingShadowSquareTextureCall()
{
	const ULONG_PTR injectAddress = 0x005DCAC7;
	void** proxyFunctionAddress = &SetBuildingShadowSquareTextureAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x57,													//push edi
		0x8D, 0x45, 0xFC,										//lea eax,[ebp - 04]
		0x50,													//push eax
		0x8D, 0x4D, 0xF4,										//lea ecx,[ebp - 0C]
		0x51,													//push ecx
		0x8D, 0x55, 0xF0,										//lea edx,[ebp - 10]
		0x52,													//push edx
		0x8D, 0x45, 0xF8,										//lea eax,[ebp - 08]
		0x50,													//push eax
		0x8B, 0x0D, 0x78, 0xCA, 0x9F, 0x00,						//mov ecx,[009FCA78]
		0x51,													//push ecx
		0x8B, 0x5D, 0x08,										//mov ebx,[ebp + 08]
		0x8B, 0xC3,												//mov eax,ebx
		0x99,													//cdq
		0x83, 0xE2, 0x3F,										//and edx,3F
		0x03, 0xC2,												//add eax,edx
		0xC1, 0xF8, 0x06,										//sar eax,06
		0x50,													//push eax
		0x8B, 0x4D, 0x0C,										//mov ecx,[ebp + 0C]
		0x51,													//push ecx
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],		//call DWRD PTR ds:${proxyAddress}
		0x8B, 0xF8,												//mov edi,eax
		0x85, 0xFF,												//test edi,edi
		0x0F, 0x84, 0x08, 0x03, 0x00, 0x00,						//je 005DCE0A
		0xE9, 0x31, 0x00, 0x00, 0x00							//jmp 0x5DCB46
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}
void ShadowRenderProxyInjector::HookRegisterBuildingShadowSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005CAC00;
	void** proxyFunctionAddress = &RegisterBuildingShadowSquareRenderingAddress;
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
void ShadowRenderProxyInjector::HookCommitBuildingShadowCall()
{
	const ULONG_PTR injectAddress = 0x005CAC73;
	void** proxyFunctionAddress = &CommitBuildingShadowAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

ShadowRenderProxyInjector::ShadowRenderProxyInjector()
{
	proxy = new ShadowRenderProxy();
	SetUnitShadowSquareTextureAddress = (LPVOID)((ULONG_PTR)SetUnitShadowSquareTextureWrapper);
	RegisterUnitShadowSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterUnitShadowSquareRenderingWrapper);
	CommitUnitShadowAddress = (LPVOID)((ULONG_PTR)CommitUnitShadowWrapper);
	SetBuildingShadowSquareTextureAddress = (LPVOID)((ULONG_PTR)SetBuildingShadowSquareTextureWrapper);
	RegisterBuildingShadowSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterBuildingShadowSquareRenderingWrapper);
	CommitBuildingShadowAddress = (LPVOID)((ULONG_PTR)CommitBuildingShadowWrapper);
}
void ShadowRenderProxyInjector::Inject()
{
	HookSetUnitShadowSquareTextureCall();
	HookRegisterUnitShadowSquareRenderCall();
	HookCommitUnitShadowCall();

	HookSetBuildingShadowSquareTextureCall();
	HookRegisterBuildingShadowSquareRenderCall();
	HookCommitBuildingShadowCall();
}
ShadowRenderProxyInjector::~ShadowRenderProxyInjector()
{
	delete proxy;
}