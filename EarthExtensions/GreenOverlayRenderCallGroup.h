#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class GreenOverlayRenderCallGroup : public RenderCallGroup
{
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	static DWORD CurrentGreenTextureNum;
	static DWORD CurrentGreenTextureUnknownValue;
};