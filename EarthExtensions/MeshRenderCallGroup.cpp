#include "pch.h"
#include "MeshRenderCallGroup.h"

LPVOID MeshRenderCallGroup::GetTextureAddress()
{
	return &TextureAddress;
}
void MeshRenderCallGroup::SetTextureAddress(LPVOID textureAddress)
{
	TextureAddress = textureAddress;
}
int MeshRenderCallGroup::GetMaxOffset()
{
	return 150;
}
DWORD MeshRenderCallGroup::GetCurrentTextureNum()
{
	return CurrentMeshTextureNum;
}
DWORD MeshRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return 4096;
}

DWORD MeshRenderCallGroup::GetVertexCountPerCall()
{
	return 3;
}

DWORD MeshRenderCallGroup::GetIndexCountPerCall()
{
	return 3;
}

void MeshRenderCallGroup::AddSquare(D3DVERTEX* vertices)
{
	static WORD indices[] = { 0, 1, 2 };
	RenderCallGroup::AddSquare(vertices, indices);
}
LPVOID MeshRenderCallGroup::CurrentMeshTextureAddress;
DWORD MeshRenderCallGroup::CurrentMeshTextureNum;