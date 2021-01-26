#include "pch.h"
#include "TerrainRenderProxy.h"

TerrainRenderProxy::TerrainRenderProxy()
{
	for (int i = 0; i < 1024; i++)
	{
		groundCalls[i] = new GroundRenderCallGroup(i);
		navMeshCalls[i] = new NavMeshRenderCallGroup(i);
		greenCalls[i] = new GreenOverlayRenderCallGroup(i);
	}
	resourceRenderCall = new ResourceRenderCallGroup();
}
TerrainRenderProxy::~TerrainRenderProxy()
{
	for (int i = 0; i < 1024; i++)
	{
		delete groundCalls[i];
		delete navMeshCalls[i];
		delete greenCalls[i];
	}
	delete resourceRenderCall;
}

HRESULT TerrainRenderProxy::SetGroundTexture(DWORD textureNum, DWORD textureSize)
{
	GroundRenderCallGroup::CurrentGroundTextureNum = textureNum;
	GroundRenderCallGroup::CurrentGroundTextureUnknownValue = textureSize;
	return 0;
}

HRESULT TerrainRenderProxy::RegisterGroundSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	groundCalls[GroundRenderCallGroup::CurrentGroundTextureNum]->AddSquare(lpvVertices, lpwIndices);
	return 0;
}

HRESULT TerrainRenderProxy::SetNavMeshTexture(DWORD textureNum)
{
	NavMeshRenderCallGroup::CurrentNavMeshTextureNum = textureNum;
	return 0;
}

HRESULT TerrainRenderProxy::RegisterNavMeshSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	navMeshCalls[NavMeshRenderCallGroup::CurrentNavMeshTextureNum]->AddSquare(lpvVertices, lpwIndices);
	return 0;
}

HRESULT TerrainRenderProxy::SetGreenTexture(DWORD textureNum, DWORD textureSize)
{
	GreenOverlayRenderCallGroup::CurrentGreenTextureNum = textureNum;
	GreenOverlayRenderCallGroup::CurrentGreenTextureUnknownValue = textureSize;
	return 0;
}

HRESULT TerrainRenderProxy::RegisterGreenSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	greenCalls[GreenOverlayRenderCallGroup::CurrentGreenTextureNum]->AddSquare(lpvVertices, lpwIndices);
	return 0;
}

HRESULT TerrainRenderProxy::RegisterResourceSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	resourceRenderCall->AddSquare(lpvVertices, lpwIndices);
	return 0;
}

HRESULT TerrainRenderProxy::Commit()
{
	for (int i = 0; i < 1024; i++)
	{
		groundCalls[i]->Render();
	}
	for (int i = 0; i < 1024; i++)
	{
		navMeshCalls[i]->Render();
	}
	for (int i = 0; i < 1024; i++)
	{
		greenCalls[i]->Render();
	}

	resourceRenderCall->Render();

	//call replaced asm code
	//005C9BCB 6A 01                push        1  
	//005C9BCD FF 15 D4 E2 9F 00    call        dword ptr ds : [9FE2D4h]
	typedef void (__stdcall *originalCall)(WORD param);

	void* originalFunctionPointer = (void*)(*((long*)0x009FE2D4));
	originalCall call = (originalCall)(originalFunctionPointer);
	call(1);
	return 0;
}