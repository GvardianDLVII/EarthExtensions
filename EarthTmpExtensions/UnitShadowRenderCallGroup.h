#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class UnitShadowRenderCallGroup : public SquareRenderCallGroup
{
private:
	LPVOID TextureAddress;
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	UnitShadowRenderCallGroup(DWORD textureNum, LPVOID textureAddress);
	static LPVOID CurrentUnitShadowTextureAddress;
	static DWORD CurrentUnitShadowTextureNum;
};