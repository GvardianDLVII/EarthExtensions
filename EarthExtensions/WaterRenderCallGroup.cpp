#include "pch.h"
#include "WaterRenderCallGroup.h"

LPVOID WaterRenderCallGroup::GetTextureAddress()
{
	return (LPVOID)0x00A4154C;
}
int WaterRenderCallGroup::GetMaxOffset()
{
	return 100;
}
DWORD WaterRenderCallGroup::GetCurrentTextureNum()
{
	return CurrentWaterTextureNum;
}
DWORD WaterRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return CurrentWaterTextureUnknownValue;
}
DWORD WaterRenderCallGroup::CurrentWaterTextureUnknownValue;
DWORD WaterRenderCallGroup::CurrentWaterTextureNum;

void WaterRenderCallGroup::AddSquare(D3DVERTEX* vertices)
{
	static WORD indices[] = { 0, 1, 2 };
	RenderCallGroup::AddSquare(vertices, indices);
}

DWORD WaterRenderCallGroup::GetVertexCountPerCall()
{
	return 3;
}

DWORD WaterRenderCallGroup::GetIndexCountPerCall()
{
	return 3;
}
