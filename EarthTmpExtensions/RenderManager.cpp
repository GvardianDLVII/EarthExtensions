#include "pch.h"
#include "RenderManager.h"
#include "OriginalMethods.h"

WaterRenderProxy* RenderManager::waterRenderer = 0;
WaterRenderProxyInjector* RenderManager::waterRendererInjector = 0;
MeshRenderProxy* RenderManager::meshRenderer = 0;
MeshRenderProxyInjector* RenderManager::meshRendererInjector = 0;
EffectsRenderProxy* RenderManager::effectsRenderer = 0;
EffectsRenderProxyInjector* RenderManager::effectsRendererInjector = 0;
TerrainRenderProxyInjector* RenderManager::TerrainInjector;
UnitShadowRenderProxy* RenderManager::shadowRenderer = 0;
ShadowRenderProxyInjector* RenderManager::shadowInjector;
RenderingContextType RenderManager::renderingContext = RenderingContextType::Other;

RenderManager::RenderManager()
{
	meshRenderer = new MeshRenderProxy();
	meshRendererInjector = new MeshRenderProxyInjector();
	effectsRenderer = new EffectsRenderProxy();
	effectsRendererInjector = new EffectsRenderProxyInjector();
	if (Configuration::GetEnableMeshRenderingOptimization())
	{
		meshRendererInjector->Inject();
		effectsRendererInjector->Inject();
	}
	RenderMeshesAddress = (void*)RenderMeshes;
	HookRenderMeshesCall();

	waterRenderer = new WaterRenderProxy();
	waterRendererInjector = new WaterRenderProxyInjector();
	if (Configuration::GetEnableWaterRenderingOptimization())
	{
		waterRendererInjector->Inject();
	}
	RenderWaterAndUnitShadowsAddress = (void*)RenderWaterAndUnitShadows;
	HookRenderWaterAndUnitShadowsCall();
	TerrainInjector = new TerrainRenderProxyInjector();
	if (Configuration::GetEnableTerrainRenderingOptimization())
	{
		TerrainInjector->Inject();
	}
	shadowRenderer = new UnitShadowRenderProxy();
	shadowInjector = new ShadowRenderProxyInjector();
	if (Configuration::GetEnableShadowRenderingOptimization())
	{
		shadowInjector->Inject();
	}
}
RenderManager::~RenderManager()
{
	delete meshRendererInjector;
	delete meshRenderer;
	delete effectsRendererInjector;
	delete effectsRenderer;
	delete waterRendererInjector;
	delete waterRenderer;
	delete TerrainInjector;
	delete shadowRenderer;
	delete shadowInjector;
}

RenderingContextType RenderManager::GetRenderingContext()
{
	return renderingContext;
}

WaterRenderProxy* RenderManager::GetWaterRenderer()
{
	return waterRenderer;
}

MeshRenderProxy* RenderManager::GetMeshRenderer()
{
	return meshRenderer;
}

EffectsRenderProxy* RenderManager::GetEffectsRenderer()
{
	return effectsRenderer;
}

UnitShadowRenderProxy* RenderManager::GetUnitShadowRenderer()
{
	return shadowRenderer;
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

void RenderManager::CallRenderMeshes(DWORD arg1)
{
	renderingContext = RenderingContextType::MeshesAndEffects;
	//005E2E32       E8 E9C5FFFF       call 005DF420
	typedef void(__stdcall* originalCall)(DWORD);

	void* originalFunctionPointer = (void*)0x005DF420;
	originalCall call = (originalCall)(originalFunctionPointer);
	call(arg1);
	renderingContext = RenderingContextType::Other;
	meshRenderer->CommitMesh();
	effectsRenderer->CommitEffects();
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
}
void __stdcall RenderManager::RenderWaterAndUnitShadows(DWORD arg1, DWORD arg2)
{
	if (arg1 == arg2)
		CallRenderWater();
	if(GetCameraHeight() < Configuration::GetShadowRenderThreshold())
		CallRenderUnitShadows();
}
void __stdcall RenderManager::RenderMeshes(DWORD arg1)
{
	CallRenderMeshes(arg1);
}