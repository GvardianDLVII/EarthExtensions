#include "pch.h"
#include "GreenOverlayRenderCallGroup.h"

GreenOverlayRenderCallGroup::GreenOverlayRenderCallGroup(DWORD textureNum) : SquareRenderCallGroup(textureNum)
{
}
LPVOID GreenOverlayRenderCallGroup::GetTextureAddress()
{
	return (LPVOID)0x00A41520;
}
int GreenOverlayRenderCallGroup::GetMaxOffset()
{
	return Configuration::GetGreenOverlayRenderBufferSize();
}
DWORD GreenOverlayRenderCallGroup::GetCurrentTextureNum()
{
	return CurrentGreenTextureNum;
}
DWORD GreenOverlayRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return CurrentGreenTextureUnknownValue;
}

DWORD GreenOverlayRenderCallGroup::CurrentGreenTextureNum;
DWORD GreenOverlayRenderCallGroup::CurrentGreenTextureUnknownValue;