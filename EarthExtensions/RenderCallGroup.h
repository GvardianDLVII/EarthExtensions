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
	std::map<LPDIRECT3DTEXTURE2, D3DVERTEX*> VertexBuffer;
	std::map<LPDIRECT3DTEXTURE2, LPWORD> IndexBuffer;
	std::map<LPDIRECT3DTEXTURE2, WORD> Offset;

	virtual int GetMaxOffset() = 0;

	virtual DWORD GetVertexCountPerCall();
	virtual DWORD GetIndexCountPerCall();

	virtual void RenderPart(long offset, LPDIRECT3DTEXTURE2 texture);
public:
	RenderCallGroup2(bool translucent);
	virtual void AddSquare(D3DVERTEX* vertices, LPWORD indices);
	virtual void Render();
};