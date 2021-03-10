#include "pch.h"
#include "ZoomManager.h"
#include <chrono>
#include <ctime>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

long ZoomManager::timeLeftMs[3];
float ZoomManager::desiredZoom[3];
float ZoomManager::savedZoom[3];
long long ZoomManager::lastUpdateTime = 0;
void* ZoomManager::ChangeZoomAddress = 0;
void* ZoomManager::TickAddress = 0;

bool Enabled = false;

long ZoomManager::ToCameraIndex(long viewIndex)
{
	return *((long*)(*((long*)0x009FDF48) + viewIndex * 72 + 0x30));
}

void __stdcall ZoomManager::ChangeZoom(long viewIndex, float deltaZoom)
{
	if ((*(DWORD*)0x009FDF40) == 0) //I don't know what it is
	{
		return;
	}

	if (!Enabled)
	{
		Enable();
	}

	auto cameraIndex = ToCameraIndex(viewIndex);

	desiredZoom[cameraIndex] += deltaZoom;
	if (desiredZoom[cameraIndex] < GetMinZoom())
	{
		desiredZoom[cameraIndex] = GetMinZoom();
	}
	if (desiredZoom[cameraIndex] > GetMaxZoom())
	{
		desiredZoom[cameraIndex] = GetMaxZoom();
	}
	timeLeftMs[cameraIndex] = Configuration::GetZoomTime();
}

float ZoomManager::GetCameraZoom(long cameraIndex)
{
	return *((float*)((*((long*)(0x009FD9C4))) + 0x33 * 4 * cameraIndex + 0x1C));
}

void ZoomManager::SetCameraZoom(long cameraIndex, float newZoom)
{
	*((float*)((*((long*)(0x009FD9C4))) + 0x33 * 4 * cameraIndex + 0x1C)) = newZoom;
	savedZoom[cameraIndex] = newZoom;
}

float ZoomManager::GetMinZoom()
{
	return *((float*)0x770044);
}

float ZoomManager::GetMaxZoom()
{
	return *((float*)0x770040);
}

void ZoomManager::UpdateZoom()
{
	auto now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	auto deltaTime = (now - lastUpdateTime);
	lastUpdateTime = now;
	for (int i = 0; i < 3; i++)
	{
		float currentZoom = GetCameraZoom(i);
		if (currentZoom != savedZoom[i])
		{
			//something else modified the zoom, let's not interfere.
			savedZoom[i] = currentZoom;
			desiredZoom[i] = currentZoom;
			timeLeftMs[i] = 0;
			continue;
		}
		if (currentZoom != desiredZoom[i])
		{
			timeLeftMs[i] -= deltaTime;
			if (timeLeftMs[i] < 0)
			{
				timeLeftMs[i] = 0;
				SetCameraZoom(i, desiredZoom[i]);
				continue;
			}
			float zoomFactor = (static_cast<float>(Configuration::GetZoomTime() - timeLeftMs[i])) / Configuration::GetZoomTime();
			float deltaZoom = (desiredZoom[i] - currentZoom) * zoomFactor;
			SetCameraZoom(i, currentZoom + deltaZoom);
		}
	}
}

void ZoomManager::Tick()
{
	typedef void(__stdcall* originalCall)(void);
	void* originalFunctionPointer = (void*)0x0060A660;
	originalCall call = (originalCall)(originalFunctionPointer);
	call();

	if(Enabled)
		UpdateZoom();
}

void ZoomManager::HookChangeZoom()
{
	const ULONG_PTR injectAddress = 0x0066839E;
	ULONG relativeAddress = (ULONG)ChangeZoomAddress - (ULONG)injectAddress - 0x5;
	BYTE bytes[4];
	ToByteArray(relativeAddress, bytes);
	BYTE proxyCall[] = {
		0xE8, bytes[3], bytes[2], bytes[1], bytes[0]     //call ${relativeAddress}
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

void ZoomManager::HookTick()
{
	const ULONG_PTR injectAddress = 0x005E34A2;
	ULONG relativeAddress = (ULONG)TickAddress - (ULONG)injectAddress - 0x5;
	BYTE bytes[4];
	ToByteArray(relativeAddress, bytes);
	BYTE proxyCall[] = {
		0xE8, bytes[3], bytes[2], bytes[1], bytes[0]     //call ${relativeAddress}
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

void ZoomManager::Enable()
{
	Enabled = true;
	lastUpdateTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	for (int i = 0; i < 3; i++)
	{
		timeLeftMs[i] = 0;
		savedZoom[i] = 0;
		desiredZoom[i] = GetCameraZoom(i);
	}
}

void ZoomManager::Initialize()
{
	ChangeZoomAddress = (void*)ChangeZoom;
	TickAddress = (void*)Tick;
	HookChangeZoom();
	HookTick();
}
