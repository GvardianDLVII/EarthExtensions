#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class MeshRenderCallGroup : public RenderCallGroup
{
private:
	LPVOID TextureAddress;
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();

	virtual DWORD GetVertexCountPerCall();
	virtual DWORD GetIndexCountPerCall();
public:
	void AddSquare(D3DVERTEX* vertices);
	void SetTextureAddress(LPVOID textureAddress);
	static LPVOID CurrentMeshTextureAddress;
	static DWORD CurrentMeshTextureNum;
};