#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class UnitShadowRenderCallGroup : public RenderCallGroup2
{
private:
protected:
	virtual int GetMaxOffset();
public:
	UnitShadowRenderCallGroup(bool translucent);
};