#pragma once
#include "pch.h"
#include "WaterRenderProxy.h"
#include "WaterRenderProxyInjector.h"

class RenderManager
{
private:
	static WaterRenderProxy* waterRenderer;
	static WaterRenderProxyInjector* waterRendererInjector;
	void* RenderWaterAndUnitShadowsAddress;
	static void CallRenderWater();
	static void CallRenderUnitShadows();
	void HookRenderWaterAndUnitShadowsCall();
public:
	RenderManager();
	static void __stdcall RenderWaterAndUnitShadows(DWORD arg1, DWORD arg2);
	~RenderManager();
};
