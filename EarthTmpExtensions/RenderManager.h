#pragma once
#include "pch.h"
#include "WaterRenderProxy.h"
#include "WaterRenderProxyInjector.h"
#include "MeshRenderProxy.h"
#include "MeshRenderProxyInjector.h"
#include "TerrainRenderProxyInjector.h"
#include "ShadowRenderProxyInjector.h"

enum class RenderingContextType { Other = 0, Water = 1, UnitShadows = 2, Mesh = 3 };

class RenderManager
{
private:
	static RenderingContextType renderingContext;
	static WaterRenderProxy* waterRenderer;
	static WaterRenderProxyInjector* waterRendererInjector;
	static MeshRenderProxy* meshRenderer;
	static MeshRenderProxyInjector* meshRendererInjector;
	static TerrainRenderProxyInjector* TerrainInjector;
	static ShadowRenderProxyInjector* ShadowInjector;
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
};
