#include "pch.h"
#include "WaterRenderCallGroup.h"

WaterRenderCallGroup::WaterRenderCallGroup(bool translucent) : RenderCallGroup2(translucent)
{
}
int WaterRenderCallGroup::GetMaxOffset()
{
	return 1000;
}
void WaterRenderCallGroup::AddSquare(D3DVERTEX* vertices)
{
	static WORD indices[] = { 0, 1, 2 };
	RenderCallGroup2::AddSquare(vertices, indices);
}

DWORD WaterRenderCallGroup::GetVertexCountPerCall()
{
	return 3;
}

DWORD WaterRenderCallGroup::GetIndexCountPerCall()
{
	return 3;
}
