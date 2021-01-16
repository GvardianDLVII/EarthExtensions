#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class ResourceRenderCallGroup : public RenderCallGroup
{
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
};