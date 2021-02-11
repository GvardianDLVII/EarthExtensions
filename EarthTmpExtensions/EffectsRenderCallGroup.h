#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class EffectsRenderCallGroup : public TriangleRenderCallGroup
{
private:
	LPVOID TextureAddress;
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	EffectsRenderCallGroup(LPVOID textureAddress);
	static LPVOID CurrentEffectTextureAddress;
};
