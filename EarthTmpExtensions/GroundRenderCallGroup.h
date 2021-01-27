#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class GroundRenderCallGroup : public SquareRenderCallGroup
{
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	GroundRenderCallGroup(DWORD textureNum);
	static DWORD CurrentGroundTextureNum;
	static DWORD CurrentGroundTextureUnknownValue;
};