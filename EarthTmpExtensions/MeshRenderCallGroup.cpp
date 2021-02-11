#include "pch.h"
#include "MeshRenderCallGroup.h"

MeshRenderCallGroup::MeshRenderCallGroup(DWORD textureNum, LPVOID textureAddress) : TriangleRenderCallGroup(textureNum)
{
	TextureAddress = textureAddress;
}
LPVOID MeshRenderCallGroup::GetTextureAddress()
{
	return &TextureAddress;
}
int MeshRenderCallGroup::GetMaxOffset()
{
	return Configuration::GetMeshRenderBufferSize();
}
DWORD MeshRenderCallGroup::GetCurrentTextureNum()
{
	return CurrentMeshTextureNum;
}
DWORD MeshRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return 4096;
}
LPVOID MeshRenderCallGroup::CurrentMeshTextureAddress;
DWORD MeshRenderCallGroup::CurrentMeshTextureNum;
