#include "pch.h"
#include "WaterRenderCallGroup.h"

WaterRenderCallGroup::WaterRenderCallGroup(DWORD textureNum) : TriangleRenderCallGroup(textureNum)
{
}
LPVOID WaterRenderCallGroup::GetTextureAddress()
{
	return (LPVOID)0x00A4154C;
}
int WaterRenderCallGroup::GetMaxOffset()
{
	return 150;
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
