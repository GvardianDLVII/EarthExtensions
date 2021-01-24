#include "pch.h"
#include "RenderCallGroup.h"
#include "RenderManager.h"
#include "OriginalMethods.h"

SquareRenderCallGroup::SquareRenderCallGroup(bool translucent) : RenderCallGroup2(translucent)
{
}

void SquareRenderCallGroup::RenderPart(long partIndex, LPDIRECT3DTEXTURE2 texture)
{
	RevEng5C34F0(translucent ? 0 : 0x70, texture);
	GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, (LPVOID)VertexBuffer[partIndex], Offset[partIndex] * GetVertexCountPerCall(), IndexBuffer[partIndex], Offset[partIndex] * GetIndexCountPerCall(), 0);
}
void SquareRenderCallGroup::AddSquare(D3DVERTEX* vertices, LPWORD indices)
{
	auto it = ArrayIndices.find((ULONG)RenderManager::GetCurrentTextureContext());
	WORD index = 0;
	if (it == ArrayIndices.end())
	{
		D3DVERTEX* bufferedVeritices = new D3DVERTEX[GetMaxOffset() * GetVertexCountPerCall()];
		LPWORD bufferedIndices = new WORD[GetMaxOffset() * GetIndexCountPerCall()];
		VertexBuffer[lastIndex] = bufferedVeritices;
		IndexBuffer[lastIndex] = bufferedIndices;
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
	LPWORD copiedIndices = IndexBuffer[index];
	memcpy(copiedIndices + currentOffset * GetIndexCountPerCall(), indices, GetIndexCountPerCall() * sizeof(WORD));
	for (int i = currentOffset * GetIndexCountPerCall(); i < (currentOffset + 1) * GetIndexCountPerCall(); i++)
	{
		copiedIndices[i] += currentOffset * GetVertexCountPerCall();
	}
	currentOffset++;
	Offset[index] = currentOffset;
	if (currentOffset == GetMaxOffset())
	{
		RenderPart(index, RenderManager::GetCurrentTextureContext());
		Offset[index] = 0;
	}
}
WORD SquareRenderCallGroup::GetVertexCountPerCall()
{
	return 4;
}
WORD SquareRenderCallGroup::GetIndexCountPerCall()
{
	return 6;
}
