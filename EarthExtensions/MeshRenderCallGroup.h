#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class MeshRenderCallGroup : public TriangleRenderCallGroup
{
protected:
	virtual int GetMaxOffset();
public:
	MeshRenderCallGroup(bool translucent);
};