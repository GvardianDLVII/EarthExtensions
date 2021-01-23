#pragma once
#include "pch.h"

void TmpSetTextureCall(LPVOID textureAddress, DWORD texturePartNum, DWORD textureUnknownValue);



IDirect3DDevice3* GetD3DDevice();
void RevEng5C34F0(long arg1, LPDIRECT3DTEXTURE2 texture);

float GetCameraActorPosX();
float GetCameraActorPosY();
float GetCameraHeight();
