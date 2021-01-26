#include "pch.h"
#include "RenderCallGroup.h"

TriangleRenderCallGroup::TriangleRenderCallGroup(DWORD textureNum) : RenderCallGroup(textureNum)
{
}
void TriangleRenderCallGroup::RenderPart(WORD partIndex, DWORD textureUnknownValue)
{
	TmpSetTextureCall(GetTextureAddress(), GetTextureNum(), textureUnknownValue);
	GetD3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, (LPVOID)VertexBuffer[partIndex], Offset[partIndex] * GetVertexCountPerCall(), 0);
}
void TriangleRenderCallGroup::AddTriangle(D3DVERTEX* vertices)
{
	auto it = ArrayIndices.find(GetCurrentTextureUnknownValue());
	WORD index = 0;
	if (it == ArrayIndices.end())
	{
		D3DVERTEX* bufferedVeritices = new D3DVERTEX[GetMaxOffset() * GetVertexCountPerCall()];
		VertexBuffer[lastIndex] = bufferedVeritices;
		index = lastIndex;
		ArrayIndices[GetCurrentTextureUnknownValue()] = index;
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
		RenderPart(index, GetCurrentTextureUnknownValue());
		Offset[index] = 0;
	}
}
WORD TriangleRenderCallGroup::GetVertexCountPerCall()
{
	return 3;
}
