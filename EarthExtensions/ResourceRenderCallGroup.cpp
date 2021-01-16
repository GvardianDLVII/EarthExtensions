#include "pch.h"
#include "ResourceRenderCallGroup.h"


LPVOID ResourceRenderCallGroup::GetTextureAddress()
{
	return (LPVOID)0x00A4153C;
}
int ResourceRenderCallGroup::GetMaxOffset()
{
	return 10000;
}
DWORD ResourceRenderCallGroup::GetCurrentTextureNum()
{
	return 0;
}
DWORD ResourceRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return 4096;
}