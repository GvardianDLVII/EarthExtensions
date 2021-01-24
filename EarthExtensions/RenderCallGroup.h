#pragma once

#include "pch.h"

byte proxyCall[];

class RenderCallGroup
{
protected:
	std::map<long, D3DVERTEX*> VertexBuffer;
	std::map<long, LPWORD> IndexBuffer;
	std::map<long, WORD> Offset;

	virtual int GetMaxOffset() = 0;
	virtual LPVOID GetTextureAddress() = 0;
	virtual DWORD GetCurrentTextureNum() = 0;
	virtual DWORD GetCurrentTextureUnknownValue() = 0;

	virtual DWORD GetVertexCountPerCall();
	virtual DWORD GetIndexCountPerCall();

	IDirect3DDevice3* GetD3DDevice();

	void CallOriginalSetTexture(DWORD texturePartNum, DWORD textureUnknownValue);

	void RenderPart(long offset, DWORD texturePartNum, DWORD textureUnknownValue);
public:
	void AddSquare(D3DVERTEX* vertices, LPWORD indices);
	void Render(DWORD textureNum);
	void Clear();
};

class RenderCallGroup2
{
protected:
	bool translucent;
	std::map<ULONG, WORD> ArrayIndices;
	D3DVERTEX* VertexBuffer[10000];
	WORD Offset[10000];
	WORD lastIndex;

	virtual int GetMaxOffset() = 0;

	virtual WORD GetVertexCountPerCall() = 0;

	virtual void RenderPart(long partIndex, LPDIRECT3DTEXTURE2 texture) = 0;
public:
	RenderCallGroup2(bool translucent);
	virtual void Render();
};

class SquareRenderCallGroup : public RenderCallGroup2
{
protected:
	WORD* IndexBuffer[10000];
	virtual WORD GetIndexCountPerCall();
	virtual WORD GetVertexCountPerCall();
	virtual void RenderPart(long partIndex, LPDIRECT3DTEXTURE2 texture);
public:
	SquareRenderCallGroup(bool translucent);
	virtual void AddSquare(D3DVERTEX* vertices, LPWORD indices);
};

class TriangleRenderCallGroup : public RenderCallGroup2
{
protected:
	virtual WORD GetVertexCountPerCall();
	virtual void RenderPart(long partIndex, LPDIRECT3DTEXTURE2 texture);
public:
	TriangleRenderCallGroup(bool translucent);
	virtual void AddTriangle(D3DVERTEX* vertices);
};