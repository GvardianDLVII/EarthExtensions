#pragma once
#include "pch.h"
#include "WaterRenderProxy.h"
#include "WaterRenderProxyInjector.h"

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
	void* RenderWaterAndUnitShadowsAddress;
	static void CallRenderWater();
	static void CallRenderUnitShadows();
	void HookRenderWaterAndUnitShadowsCall();
public:
	static LPDIRECT3DTEXTURE2 GetCurrentTextureContext();
	static bool GetTranslucentContext();
	static RenderingContextType GetRenderingContext();
	RenderManager();
	static void __stdcall RenderWaterAndUnitShadows(DWORD arg1, DWORD arg2);
	~RenderManager();
};
