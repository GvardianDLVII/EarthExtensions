#pragma once

#include "pch.h"
#include "OriginalMethods.h"

class RenderCallGroup
{
protected:
	std::map<ULONG, WORD> ArrayIndices;
	D3DVERTEX* VertexBuffer[256];
	WORD Offset[256];;
	WORD lastIndex;
	DWORD textureNum;

	virtual int GetMaxOffset() = 0;
	virtual LPVOID GetTextureAddress() = 0;
	DWORD GetTextureNum();
	virtual DWORD GetCurrentTextureNum() = 0;
	virtual DWORD GetCurrentTextureUnknownValue() = 0;
	virtual WORD GetVertexCountPerCall() = 0;


	virtual void RenderPart(WORD partIndex, DWORD textureUnknownValue) = 0;
public:
	RenderCallGroup(DWORD textureNum);
	void Render();
};
class SquareRenderCallGroup : public RenderCallGroup
{
protected:
	WORD* IndexBuffer[256];
	virtual WORD GetIndexCountPerCall();
	virtual WORD GetVertexCountPerCall();
	virtual void RenderPart(WORD partIndex, DWORD textureUnknownValue);
public:
	SquareRenderCallGroup(DWORD textureNum);
	void AddSquare(D3DVERTEX* vertices, LPWORD indices);
};
class TriangleRenderCallGroup : public RenderCallGroup
{
protected:
	virtual WORD GetVertexCountPerCall();
	virtual void RenderPart(WORD partIndex, DWORD textureUnknownValue);
public:
	TriangleRenderCallGroup(DWORD textureNum);
	void AddTriangle(D3DVERTEX* vertices);
};
