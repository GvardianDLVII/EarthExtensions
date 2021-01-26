#include "pch.h"
#include "GroundRenderCallGroup.h"

GroundRenderCallGroup::GroundRenderCallGroup(DWORD textureNum) : SquareRenderCallGroup(textureNum)
{
}
LPVOID GroundRenderCallGroup::GetTextureAddress()
{
	return (LPVOID)0x00A41550;
}
int GroundRenderCallGroup::GetMaxOffset()
{
	return 150;
}
DWORD GroundRenderCallGroup::GetCurrentTextureNum()
{
	return CurrentGroundTextureNum;
}
DWORD GroundRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return CurrentGroundTextureUnknownValue;
}
DWORD GroundRenderCallGroup::CurrentGroundTextureNum;
DWORD GroundRenderCallGroup::CurrentGroundTextureUnknownValue;