#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class GreenOverlayRenderCallGroup : public SquareRenderCallGroup
{
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	GreenOverlayRenderCallGroup(DWORD textureNum);
	static DWORD CurrentGreenTextureNum;
	static DWORD CurrentGreenTextureUnknownValue;
};