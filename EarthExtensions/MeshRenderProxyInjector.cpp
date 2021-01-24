#include "pch.h"
#include "MeshRenderProxyInjector.h"
#include "OriginalMethods.h"
#include "RenderManager.h"

MeshRenderProxy* MeshRenderProxyInjector::meshRenderer = 0;

HRESULT __stdcall MeshRenderProxyInjector::RegisterMeshTriangleRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _vertCount, DWORD _flags)
{
	if (RenderManager::GetRenderingContext() == RenderingContextType::Mesh)
	{
		return meshRenderer->RegisterMeshTriangleRendering(lpvVertices);
	}
	else //default render action
	{
		return GetD3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, lpvVertices, 3, 0);
	}
}

MeshRenderProxyInjector::MeshRenderProxyInjector(MeshRenderProxy* meshRenderer)
{
	this->meshRenderer = meshRenderer;
	RegisterMeshTriangleRenderingAddress = (LPVOID)((ULONG_PTR)RegisterMeshTriangleRenderingWrapper);
}

void MeshRenderProxyInjector::Inject()
{
	HookRegisterMeshTriangleRenderCall();
}

void MeshRenderProxyInjector::HookRegisterMeshTriangleRenderCall()
{
	const ULONG_PTR injectAddress = 0x005C32AD;
	void** proxyFunctionAddress = &RegisterMeshTriangleRenderingAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],		//call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}
