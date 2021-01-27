#pragma once
#include "pch.h"

class Configuration
{
private:
	static float ShadowRenderThreshold;

	static int GroundRenderBufferSize;
	static int NavMeshRenderBufferSize;
	static int GreenOverlayRenderBufferSize;
	static int ResourcesRenderBufferSize;
	static int WaterRenderBufferSize;
	static int ShadowRenderBufferSize;
	static int MeshRenderBufferSize;

	static bool EnableRenderOverflowCrashFix;
	static bool EnableTerrainRenderingOptimization;
	static bool EnableWaterRenderingOptimization;
	static bool EnableShadowRenderingOptimization;
	static bool EnableMeshRenderingOptimization;

public:
	static void ReadConfig();

	static float GetShadowRenderThreshold();

	static int GetGroundRenderBufferSize();
	static int GetNavMeshRenderBufferSize();
	static int GetGreenOverlayRenderBufferSize();
	static int GetResourcesRenderBufferSize();
	static int GetWaterRenderBufferSize();
	static int GetShadowRenderBufferSize();
	static int GetMeshRenderBufferSize();

	static bool GetEnableRenderOverflowCrashFix();
	static bool GetEnableTerrainRenderingOptimization();
	static bool GetEnableWaterRenderingOptimization();
	static bool GetEnableShadowRenderingOptimization();
	static bool GetEnableMeshRenderingOptimization();
};