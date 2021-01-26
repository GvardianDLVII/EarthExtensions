#pragma once
#include "pch.h"

void TmpSetTextureCall(LPVOID textureAddress, DWORD texturePartNum, DWORD textureUnknownValue);

IDirect3DDevice3* GetD3DDevice();
float GetCameraActorPosX();
float GetCameraActorPosY();
float GetCameraHeight();
