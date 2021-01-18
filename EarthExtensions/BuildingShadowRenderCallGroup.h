#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class BuildingShadowRenderCallGroup : public RenderCallGroup
{
private:
	DWORD TextureInfoParams[7];
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	BuildingShadowRenderCallGroup();
	void SetTextureInfoParams(DWORD params[7]);
	static DWORD CurrentBuildingShadowTextureInfo[7];
	static DWORD CalculateTextureAddress(DWORD params[]);
};