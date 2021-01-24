#include "pch.h"
#include "RenderManager.h"
#include "RenderCallGroup.h"
#include "OriginalMethods.h"

WaterRenderProxy* RenderManager::waterRenderer = 0;
WaterRenderProxyInjector* RenderManager::waterRendererInjector = 0;
UnitShadowRenderProxy* RenderManager::unitShadowRenderer = 0;
ShadowRenderProxyInjector* RenderManager::unitShadowRendererInjector = 0;
MeshRenderProxy* RenderManager::meshRenderer = 0;
MeshRenderProxyInjector* RenderManager::meshRendererInjector = 0;
RenderingContextType RenderManager::renderingContext = RenderingContextType::Other;
LPDIRECT3DTEXTURE2 RenderManager::currentTextureContext = 0;
bool RenderManager::translucentContext = false;
long long interceptedCalls = 0;
long long otherCalls = 0;

RenderManager::RenderManager()
{
	waterRenderer = new WaterRenderProxy();
	waterRendererInjector = new WaterRenderProxyInjector(waterRenderer);
	waterRendererInjector->Inject();

	unitShadowRenderer = new UnitShadowRenderProxy();
	unitShadowRendererInjector = new ShadowRenderProxyInjector(unitShadowRenderer);
	unitShadowRendererInjector->Inject();

	meshRenderer = new MeshRenderProxy();
	meshRendererInjector = new MeshRenderProxyInjector(meshRenderer);
	meshRendererInjector->Inject();

	RenderWaterAndUnitShadowsAddress = (void*)RenderWaterAndUnitShadows;
	HookRenderWaterAndUnitShadowsCall();
	RenderMeshesAddress = (void*)RenderMeshes;
	HookRenderMeshesCall();

	SetTextureCallAddress = (void*)SetTextureCall;
	HookSetTextureCall();
}
RenderManager::~RenderManager()
{
	delete waterRendererInjector;
	delete waterRenderer;
	delete unitShadowRendererInjector;
	delete unitShadowRenderer;
	delete meshRendererInjector;
	delete meshRenderer;
}

void RenderManager::SetTextureCall(long arg1, LPDIRECT3DTEXTURE2 texture)
{
	if (renderingContext != RenderingContextType::Other)
	{
		translucentContext = arg1 != 0x70;
		currentTextureContext = texture;
		RevEng5C34F0(arg1, texture);
	}
	else
	{
		RevEng5C34F0(arg1, texture);
	}
}

bool RenderManager::GetTranslucentContext()
{
	return translucentContext;
}

LPDIRECT3DTEXTURE2 RenderManager::GetCurrentTextureContext()
{
	return currentTextureContext;
}

RenderingContextType RenderManager::GetRenderingContext()
{
	return renderingContext;
}

void RenderManager::HookSetTextureCall()
{
	const ULONG_PTR injectAddress = 0x005C34F0;
	void** proxyFunctionAddress = &SetTextureCallAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x55,													//push ebp
		0x8B, 0xEC,												//mov ebp,esp
		0x56,													//push esi
		0x57,													//push edi
		0x8B, 0x75, 0x08,										//mov esi,[ebp + 08]
		0x8B, 0x56, 0x60,										//mov edx,[esi + 60]
		0x52,													//push edx			//textureAddress
		0xFF, 0x76, 0x04,										//push[esi + 04]
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x5F,													//pop edi
		0x5E,													//pop esi
		0x5D,													//pop ebp
		0xC2, 0x04, 0x00										//ret 0004
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

void RenderManager::HookRenderWaterAndUnitShadowsCall()
{
	const ULONG_PTR injectAddress = 0x005E2E58;
	void** proxyFunctionAddress = &RenderWaterAndUnitShadowsAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0xFF, 0xB4, 0x8A, 0x84, 0x00, 0x00, 0x00,				//push DWORD PTR [edx+ecx*4+84h]
		0x56,													//push esi
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

void RenderManager::HookRenderMeshesCall()
{
	const ULONG_PTR injectAddress = 0x005E2E32;
	ULONG relativeAddress = (ULONG)RenderMeshesAddress - (ULONG)0x005E2E37;
	byte bytes[4];
	ToByteArray(relativeAddress, bytes);
	byte proxyCall[] = {
		0xE8, bytes[3], bytes[2], bytes[1], bytes[0]     //call ${relativeAddress}
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

void RenderManager::CallRenderWater()
{
	renderingContext = RenderingContextType::Water;
	//0005E2E61      E8 3AAC0300       call 0061DAA0
	typedef void(__stdcall* originalCall)(void);

	void* originalFunctionPointer = (void*)0x0061DAA0;
	originalCall call = (originalCall)(originalFunctionPointer);
	call();
	renderingContext = RenderingContextType::Other;
	waterRenderer->CommitWater();
}
void RenderManager::CallRenderUnitShadows()
{
	renderingContext = RenderingContextType::UnitShadows;
	//005E2E66       E8 85DDFFFF       call 005E0BF0
	typedef void(__stdcall* originalCall)(void);

	void* originalFunctionPointer = (void*)0x005E0BF0;
	originalCall call = (originalCall)(originalFunctionPointer);
	call();
	renderingContext = RenderingContextType::Other;
	unitShadowRenderer->CommitUnitShadow();
}
void RenderManager::CallRenderMeshes(DWORD arg1)
{
	renderingContext = RenderingContextType::Mesh;
	//005E2E32       E8 E9C5FFFF       call 005DF420
	typedef void(__stdcall* originalCall)(DWORD);

	void* originalFunctionPointer = (void*)0x005DF420;
	originalCall call = (originalCall)(originalFunctionPointer);
	call(arg1);
	renderingContext = RenderingContextType::Other;
	meshRenderer->CommitMesh();
}
void __stdcall RenderManager::RenderWaterAndUnitShadows(DWORD arg1, DWORD arg2)
{
	if (arg1 == arg2)
		CallRenderWater();
	if(GetCameraHeight()<50.0f)
		CallRenderUnitShadows();
}
void __stdcall RenderManager::RenderMeshes(DWORD arg1)
{
	CallRenderMeshes(arg1);
}