#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class WaterGreenOverlayRenderCallGroup : public TriangleRenderCallGroup
{
private:
	LPVOID TextureAddress;
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	WaterGreenOverlayRenderCallGroup(DWORD textureNum, LPVOID textureAddress);
	static LPVOID CurrentWaterTextureAddress;
	static DWORD CurrentWaterTextureUnknownValue;
	static DWORD CurrentWaterTextureNum;
};