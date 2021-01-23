#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class WaterRenderCallGroup : public RenderCallGroup2
{
protected:
	virtual int GetMaxOffset();

	virtual DWORD GetVertexCountPerCall();
	virtual DWORD GetIndexCountPerCall();
public:
	WaterRenderCallGroup(bool translucent);
	void AddSquare(D3DVERTEX* vertices);
};