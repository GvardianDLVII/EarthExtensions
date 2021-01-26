#pragma once

#include "pch.h"
#include "RenderCallGroup.h"

class MeshRenderCallGroup : public TriangleRenderCallGroup
{
private:
	LPVOID TextureAddress;
protected:
	virtual LPVOID GetTextureAddress();
	virtual int GetMaxOffset();
	virtual DWORD GetCurrentTextureNum();
	virtual DWORD GetCurrentTextureUnknownValue();
public:
	MeshRenderCallGroup(DWORD textureNum, LPVOID textureAddress);
	static LPVOID CurrentMeshTextureAddress;
	static DWORD CurrentMeshTextureNum;
};