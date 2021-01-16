#include "pch.h"
#include "GreenOverlayRenderCallGroup.h"


LPVOID GreenOverlayRenderCallGroup::GetTextureAddress()
{
	return (LPVOID)0x00A41520;
}
int GreenOverlayRenderCallGroup::GetMaxOffset()
{
	return 10000;
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