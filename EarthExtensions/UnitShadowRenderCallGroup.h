#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class UnitShadowRenderCallGroup : public SquareRenderCallGroup
{
private:
protected:
	virtual int GetMaxOffset();
public:
	UnitShadowRenderCallGroup(bool translucent);
};