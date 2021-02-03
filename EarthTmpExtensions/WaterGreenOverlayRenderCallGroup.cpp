#include "pch.h"
#include "WaterGreenOverlayRenderCallGroup.h"

WaterGreenOverlayRenderCallGroup::WaterGreenOverlayRenderCallGroup(DWORD textureNum, LPVOID textureAddress) : TriangleRenderCallGroup(textureNum)
{
	TextureAddress = textureAddress;
}
LPVOID WaterGreenOverlayRenderCallGroup::GetTextureAddress()
{
	return TextureAddress;
}
int WaterGreenOverlayRenderCallGroup::GetMaxOffset()
{
	return Configuration::GetWaterGreenOverlayRenderBufferSize();
}
DWORD WaterGreenOverlayRenderCallGroup::GetCurrentTextureNum()
{
	return CurrentWaterTextureNum;
}
DWORD WaterGreenOverlayRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return CurrentWaterTextureUnknownValue;
}
LPVOID WaterGreenOverlayRenderCallGroup::CurrentWaterTextureAddress;
DWORD WaterGreenOverlayRenderCallGroup::CurrentWaterTextureUnknownValue;
DWORD WaterGreenOverlayRenderCallGroup::CurrentWaterTextureNum;
