#include "pch.h"
#include "RenderCallGroup.h"
#include "RenderManager.h"
#include "OriginalMethods.h"

TriangleRenderCallGroup::TriangleRenderCallGroup(bool translucent) : RenderCallGroup2(translucent)
{
}

void TriangleRenderCallGroup::RenderPart(long partIndex, LPDIRECT3DTEXTURE2 texture)
{
	RevEng5C34F0(translucent ? 0 : 0x70, texture);
	GetD3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, (LPVOID)VertexBuffer[partIndex], Offset[partIndex] * GetVertexCountPerCall(), 0);
}
void TriangleRenderCallGroup::AddTriangle(D3DVERTEX* vertices)
{
	auto it = ArrayIndices.find((ULONG)RenderManager::GetCurrentTextureContext());
	WORD index = 0;
	if (it == ArrayIndices.end())
	{
		D3DVERTEX* bufferedVeritices = new D3DVERTEX[GetMaxOffset() * GetVertexCountPerCall()];
		VertexBuffer[lastIndex] = bufferedVeritices;
		index = lastIndex;
		ArrayIndices[(ULONG)RenderManager::GetCurrentTextureContext()] = index;
		lastIndex++;
		if (lastIndex > 10000) throw EXCEPTION_ARRAY_BOUNDS_EXCEEDED;
	}
	else
	{
		index = it->second;
	}
	WORD currentOffset = Offset[index];
	memcpy(VertexBuffer[index] + currentOffset * GetVertexCountPerCall(), vertices, GetVertexCountPerCall() * sizeof(D3DVERTEX));
	currentOffset++;
	Offset[index] = currentOffset;
	if (currentOffset == GetMaxOffset())
	{
		RenderPart(index, RenderManager::GetCurrentTextureContext());
		Offset[index] = 0;
	}
}
WORD TriangleRenderCallGroup::GetVertexCountPerCall()
{
	return 3;
}
