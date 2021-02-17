#pragma once
class ZoomManager
{
	static long long lastUpdateTime;
	static long timeLeftMs[3];
	static float desiredZoom[3];
	static float savedZoom[3];
	static void __stdcall ChangeZoom(long viewIndex, float deltaZoom);
	static float GetViewportZoom(long viewIndex);
	static void SetViewportZoom(long viewIndex, float newZoom);
	static float GetMinZoom();
	static float GetMaxZoom();
	static void UpdateZoom();
	static void __stdcall Tick();
	static void* ChangeZoomAddress;
	static void* TickAddress;
	static void HookChangeZoom();
	static void HookTick();
	static void Enable();
public:
	static void Initialize();
};

