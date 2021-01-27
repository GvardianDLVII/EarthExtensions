#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class WaterRenderCallGroup : public TriangleRenderCallGroup
{
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	WaterRenderCallGroup(DWORD textureNum);
	static DWORD CurrentWaterTextureUnknownValue;
	static DWORD CurrentWaterTextureNum;
};