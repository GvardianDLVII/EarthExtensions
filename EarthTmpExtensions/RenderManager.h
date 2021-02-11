#pragma once
#include "pch.h"
#include "WaterRenderProxy.h"
#include "WaterRenderProxyInjector.h"
#include "MeshRenderProxy.h"
#include "MeshRenderProxyInjector.h"
#include "EffectsRenderProxy.h"
#include "EffectsRenderProxyInjector.h"
#include "TerrainRenderProxyInjector.h"
#include "UnitShadowRenderProxy.h"
#include "ShadowRenderProxyInjector.h"

enum class RenderingContextType { Other = 0, Water = 1, UnitShadows = 2, MeshesAndEffects = 3 };

class RenderManager
{
private:
	static RenderingContextType renderingContext;
	static WaterRenderProxy* waterRenderer;
	static WaterRenderProxyInjector* waterRendererInjector;
	static MeshRenderProxy* meshRenderer;
	static MeshRenderProxyInjector* meshRendererInjector;
	static EffectsRenderProxy* effectsRenderer;
	static EffectsRenderProxyInjector* effectsRendererInjector;
	static TerrainRenderProxyInjector* TerrainInjector;
	static UnitShadowRenderProxy* shadowRenderer;
	static ShadowRenderProxyInjector* shadowInjector;
	void* RenderMeshesAddress;
	void HookRenderMeshesCall();
	void* RenderWaterAndUnitShadowsAddress;
	void HookRenderWaterAndUnitShadowsCall();

	static void CallRenderMeshes(DWORD arg1);
	static void CallRenderWater();
	static void CallRenderUnitShadows();
public:
	RenderManager();
	~RenderManager();
	static RenderingContextType GetRenderingContext();
	static void __stdcall RenderWaterAndUnitShadows(DWORD arg1, DWORD arg2);
	static void __stdcall RenderMeshes(DWORD arg1);
	static WaterRenderProxy* GetWaterRenderer();
	static MeshRenderProxy* GetMeshRenderer();
	static EffectsRenderProxy* GetEffectsRenderer();
	static UnitShadowRenderProxy* GetUnitShadowRenderer();
};
