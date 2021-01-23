#pragma once
#include "pch.h"
#include "WaterRenderProxy.h"
#include "WaterRenderProxyInjector.h"
#include "UnitShadowRenderProxy.h"
#include "ShadowRenderProxyInjector.h"

enum class RenderingContextType { Other = 0, Water = 1, UnitShadows = 2 };

class RenderManager
{
private:
	static bool translucentContext;
	static LPDIRECT3DTEXTURE2 currentTextureContext;
	static RenderingContextType renderingContext;
	void* SetTextureCallAddress;
	static void __stdcall SetTextureCall(long arg1, LPDIRECT3DTEXTURE2 textureAddress);
	void HookSetTextureCall();

	static WaterRenderProxy* waterRenderer;
	static WaterRenderProxyInjector* waterRendererInjector;
	static UnitShadowRenderProxy* unitShadowRenderer;
	static ShadowRenderProxyInjector* unitShadowRendererInjector;

	void* RenderWaterAndUnitShadowsAddress;
	void HookRenderWaterAndUnitShadowsCall();

	static void CallRenderWater();
	static void CallRenderUnitShadows();
public:
	static LPDIRECT3DTEXTURE2 GetCurrentTextureContext();
	static bool GetTranslucentContext();
	static RenderingContextType GetRenderingContext();
	RenderManager();
	static void __stdcall RenderWaterAndUnitShadows(DWORD arg1, DWORD arg2);
	~RenderManager();
};
