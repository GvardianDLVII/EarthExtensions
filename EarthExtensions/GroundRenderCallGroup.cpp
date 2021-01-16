#include "pch.h"
#include "GroundRenderCallGroup.h"


LPVOID GroundRenderCallGroup::GetTextureAddress()
{
	return (LPVOID)0x00A41550;
}
int GroundRenderCallGroup::GetMaxOffset()
{
	return 35;
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