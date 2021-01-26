#include "pch.h"
#include "UnitShadowRenderCallGroup.h"

LPVOID UnitShadowRenderCallGroup::GetTextureAddress()
{
	return &TextureAddress;
}
void UnitShadowRenderCallGroup::SetTextureAddress(LPVOID textureAddress)
{
	TextureAddress = textureAddress;
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