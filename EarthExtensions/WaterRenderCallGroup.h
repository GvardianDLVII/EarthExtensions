#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class WaterRenderCallGroup : public TriangleRenderCallGroup
{
protected:
	virtual int GetMaxOffset();
public:
	WaterRenderCallGroup(bool translucent);
};