#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class NavMeshRenderCallGroup : public RenderCallGroup
{
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	static DWORD CurrentNavMeshTextureNum;
};