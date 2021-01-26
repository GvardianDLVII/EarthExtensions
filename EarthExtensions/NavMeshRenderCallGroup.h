#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class NavMeshRenderCallGroup : public SquareRenderCallGroup
{
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	NavMeshRenderCallGroup(DWORD textureNum);
	static DWORD CurrentNavMeshTextureNum;
};