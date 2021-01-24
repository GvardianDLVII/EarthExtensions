#pragma once
#include "pch.h"
#include "WaterRenderProxy.h"
#include "WaterRenderProxyInjector.h"
#include "UnitShadowRenderProxy.h"
#include "ShadowRenderProxyInjector.h"
#include "MeshRenderProxy.h"
#include "MeshRenderProxyInjector.h"

enum class RenderingContextType { Other = 0, Water = 1, UnitShadows = 2, Mesh = 3 };

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
	static MeshRenderProxy* meshRenderer;
	static MeshRenderProxyInjector* meshRendererInjector;

	void* RenderWaterAndUnitShadowsAddress;
	void HookRenderWaterAndUnitShadowsCall();
	void* RenderMeshesAddress;
	void HookRenderMeshesCall();

	static void CallRenderMeshes(DWORD arg1);
	static void CallRenderWater();
	static void CallRenderUnitShadows();
public:
	RenderManager();
	~RenderManager();
	static LPDIRECT3DTEXTURE2 GetCurrentTextureContext();
	static bool GetTranslucentContext();
	static RenderingContextType GetRenderingContext();

	static void __stdcall RenderWaterAndUnitShadows(DWORD arg1, DWORD arg2);
	static void __stdcall RenderMeshes(DWORD arg1);
};
