#include "pch.h"
#include "ResourceRenderCallGroup.h"

ResourceRenderCallGroup::ResourceRenderCallGroup() : SquareRenderCallGroup(0)
{
}
LPVOID ResourceRenderCallGroup::GetTextureAddress()
{
	return (LPVOID)0x00A4153C;
}
int ResourceRenderCallGroup::GetMaxOffset()
{
	return Configuration::GetResourcesRenderBufferSize();
}
DWORD ResourceRenderCallGroup::GetCurrentTextureNum()
{
	return 0;
}
DWORD ResourceRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return 4096;
}