#include "pch.h"
#include "NavMeshRenderCallGroup.h"

NavMeshRenderCallGroup::NavMeshRenderCallGroup(DWORD textureNum) : SquareRenderCallGroup(textureNum)
{
}
LPVOID NavMeshRenderCallGroup::GetTextureAddress()
{
	return (LPVOID)0x00A41544;
}
int NavMeshRenderCallGroup::GetMaxOffset()
{
	return Configuration::GetNavMeshRenderBufferSize();
}
DWORD NavMeshRenderCallGroup::GetCurrentTextureNum()
{
	return CurrentNavMeshTextureNum;
}
DWORD NavMeshRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return 4096;
}
DWORD NavMeshRenderCallGroup::CurrentNavMeshTextureNum;