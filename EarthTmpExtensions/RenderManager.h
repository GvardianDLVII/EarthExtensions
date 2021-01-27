#pragma once
#include "pch.h"
#include "WaterRenderProxy.h"
#include "WaterRenderProxyInjector.h"
#include "MeshRenderProxy.h"
#include "MeshRenderProxyInjector.h"

class RenderManager
{
private:
	static WaterRenderProxy* waterRenderer;
	static WaterRenderProxyInjector* waterRendererInjector;
	static MeshRenderProxy* meshRenderer;
	static MeshRenderProxyInjector* meshRendererInjector;
	void* RenderMeshesAddress;
	void HookRenderMeshesCall();
	void* RenderWaterAndUnitShadowsAddress;
	void HookRenderWaterAndUnitShadowsCall();

	static void CallRenderMeshes(DWORD arg1);
	static void CallRenderWater();
	static void CallRenderUnitShadows();
public:
	RenderManager();
	static void __stdcall RenderWaterAndUnitShadows(DWORD arg1, DWORD arg2);
	static void __stdcall RenderMeshes(DWORD arg1);
	~RenderManager();
};
