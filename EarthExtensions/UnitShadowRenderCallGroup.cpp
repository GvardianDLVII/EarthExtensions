#include "pch.h"
#include "UnitShadowRenderCallGroup.h"

UnitShadowRenderCallGroup::UnitShadowRenderCallGroup(DWORD textureNum, LPVOID textureAddress) : SquareRenderCallGroup(textureNum)
{
	TextureAddress = textureAddress;
}
LPVOID UnitShadowRenderCallGroup::GetTextureAddress()
{
	return &TextureAddress;
}
int UnitShadowRenderCallGroup::GetMaxOffset()
{
	return 100;
}
DWORD UnitShadowRenderCallGroup::GetCurrentTextureNum()
{
	return CurrentUnitShadowTextureNum;
}
DWORD UnitShadowRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return 4096;
}
LPVOID UnitShadowRenderCallGroup::CurrentUnitShadowTextureAddress;
DWORD UnitShadowRenderCallGroup::CurrentUnitShadowTextureNum;