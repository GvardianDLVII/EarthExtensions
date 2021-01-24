#include "pch.h"
#include "RenderCallGroup.h"
#include "RenderManager.h"
#include "OriginalMethods.h"

SquareRenderCallGroup::SquareRenderCallGroup(bool translucent) : RenderCallGroup2(translucent)
{
}

void SquareRenderCallGroup::RenderPart(long offset, LPDIRECT3DTEXTURE2 texture)
{
	RevEng5C34F0(translucent ? 0 : 0x70, texture);
	GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, (LPVOID)VertexBuffer[texture], offset * GetVertexCountPerCall(), IndexBuffer[texture], offset * GetIndexCountPerCall(), 0);
}
void SquareRenderCallGroup::AddSquare(D3DVERTEX* vertices, LPWORD indices)
{
	std::map<LPDIRECT3DTEXTURE2, D3DVERTEX*>::iterator it = VertexBuffer.find(RenderManager::GetCurrentTextureContext());
	if (it == VertexBuffer.end())
	{
		D3DVERTEX* bufferedVeritices = new D3DVERTEX[GetMaxOffset() * GetVertexCountPerCall()];
		LPWORD bufferedIndices = new WORD[GetMaxOffset() * GetIndexCountPerCall()];
		VertexBuffer.insert(std::pair<LPDIRECT3DTEXTURE2, D3DVERTEX*>(RenderManager::GetCurrentTextureContext(), bufferedVeritices));
		IndexBuffer.insert(std::pair<LPDIRECT3DTEXTURE2, LPWORD>(RenderManager::GetCurrentTextureContext(), bufferedIndices));
	}
	WORD currentOffset = Offset[RenderManager::GetCurrentTextureContext()];
	memcpy(VertexBuffer[RenderManager::GetCurrentTextureContext()] + currentOffset * GetVertexCountPerCall(), vertices, GetVertexCountPerCall() * sizeof(D3DVERTEX));
	LPWORD copiedIndices = IndexBuffer[RenderManager::GetCurrentTextureContext()];
	memcpy(copiedIndices + currentOffset * GetIndexCountPerCall(), indices, GetIndexCountPerCall() * sizeof(WORD));
	for (int i = currentOffset * GetIndexCountPerCall(); i < (currentOffset + 1) * GetIndexCountPerCall(); i++)
	{
		copiedIndices[i] += currentOffset * GetVertexCountPerCall();
	}
	currentOffset++;
	Offset[RenderManager::GetCurrentTextureContext()] = currentOffset;
	if (currentOffset == GetMaxOffset())
	{
		RenderPart(currentOffset, RenderManager::GetCurrentTextureContext());
		Offset[RenderManager::GetCurrentTextureContext()] = 0;
	}
}
DWORD SquareRenderCallGroup::GetVertexCountPerCall()
{
	return 4;
}
DWORD SquareRenderCallGroup::GetIndexCountPerCall()
{
	return 6;
}
