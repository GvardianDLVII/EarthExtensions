#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class WaterRenderCallGroup : public RenderCallGroup
{
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();

	virtual DWORD GetVertexCountPerCall();
	virtual DWORD GetIndexCountPerCall();
public:
	void AddSquare(D3DVERTEX* vertices);
	static DWORD CurrentWaterTextureUnknownValue;
	static DWORD CurrentWaterTextureNum;
};