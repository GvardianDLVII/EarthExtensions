#include "pch.h"
#include "RenderCallGroup.h"
#include "RenderManager.h"
#include "OriginalMethods.h"

TriangleRenderCallGroup::TriangleRenderCallGroup(bool translucent) : RenderCallGroup2(translucent)
{
}

void TriangleRenderCallGroup::RenderPart(long offset, LPDIRECT3DTEXTURE2 texture)
{
	RevEng5C34F0(translucent ? 0 : 0x70, texture);
	GetD3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, (LPVOID)VertexBuffer[texture], offset * GetVertexCountPerCall(), 0);
}
void TriangleRenderCallGroup::AddTriangle(D3DVERTEX* vertices)
{
	std::map<LPDIRECT3DTEXTURE2, D3DVERTEX*>::iterator it = VertexBuffer.find(RenderManager::GetCurrentTextureContext());
	if (it == VertexBuffer.end())
	{
		D3DVERTEX* bufferedVeritices = new D3DVERTEX[GetMaxOffset() * GetVertexCountPerCall()];
		VertexBuffer.insert(std::pair<LPDIRECT3DTEXTURE2, D3DVERTEX*>(RenderManager::GetCurrentTextureContext(), bufferedVeritices));
	}
	WORD currentOffset = Offset[RenderManager::GetCurrentTextureContext()];
	memcpy(VertexBuffer[RenderManager::GetCurrentTextureContext()] + currentOffset * GetVertexCountPerCall(), vertices, GetVertexCountPerCall() * sizeof(D3DVERTEX));
	currentOffset++;
	Offset[RenderManager::GetCurrentTextureContext()] = currentOffset;
	if (currentOffset == GetMaxOffset())
	{
		RenderPart(currentOffset, RenderManager::GetCurrentTextureContext());
		Offset[RenderManager::GetCurrentTextureContext()] = 0;
	}
}
DWORD TriangleRenderCallGroup::GetVertexCountPerCall()
{
	return 3;
}
