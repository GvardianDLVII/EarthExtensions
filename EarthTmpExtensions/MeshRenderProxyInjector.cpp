#include "pch.h"
#include "MeshRenderProxyInjector.h"
#include "OriginalMethods.h"
#include "RenderManager.h"

HRESULT __stdcall MeshRenderProxyInjector::SetMeshTextureWrapper(LPVOID textureAddress, DWORD textureNum)
{
	if (RenderManager::GetRenderingContext() == RenderingContextType::MeshesAndEffects)
	{
		return RenderManager::GetMeshRenderer()->SetMeshTexture(textureAddress, textureNum);
	}
	else
	{
		TmpSetTextureCall(&textureAddress, textureNum, 4096);
		return 0;
	}
}
HRESULT __stdcall MeshRenderProxyInjector::RegisterMeshTriangleRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _indCount, DWORD _flags)
{
	if (RenderManager::GetRenderingContext() == RenderingContextType::MeshesAndEffects)
	{
		return RenderManager::GetMeshRenderer()->RegisterMeshTriangleRendering(lpvVertices);
	}
	else //default render action
	{
		return GetD3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, lpvVertices, 3, 0);
	}
}
void MeshRenderProxyInjector::HookSetMeshTextureCall()
{
	const ULONG_PTR injectAddress = 0x005C31C5;
	void** proxyFunctionAddress = &SetMeshTextureAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0x51,													//push ecx
		0x53,													//push ebx
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],		//call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}
void MeshRenderProxyInjector::HookRegisterMeshTriangleRenderCall()
{
	const ULONG_PTR injectAddress = 0x005C32AD;
	void** proxyFunctionAddress = &RegisterMeshTriangleRenderingAddress;
	byte bytes[4];
	ToByteArray((ULONG)proxyFunctionAddress, bytes);
	byte proxyCall[] = {
		0xFF, 0x15, bytes[3], bytes[2], bytes[1], bytes[0],     //call DWRD PTR ds:${proxyAddress}
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90,                                                   //nop
		0x90                                                    //nop
	};

	WriteProcessMemory(GetCurrentProcess(), (PVOID)injectAddress, proxyCall, sizeof(proxyCall), NULL);
}

MeshRenderProxyInjector::MeshRenderProxyInjector()
{
	SetMeshTextureAddress = (LPVOID)((ULONG_PTR)SetMeshTextureWrapper);
	RegisterMeshTriangleRenderingAddress = (LPVOID)((ULONG_PTR)RegisterMeshTriangleRenderingWrapper);
}
void MeshRenderProxyInjector::Inject()
{
	HookSetMeshTextureCall();
	HookRegisterMeshTriangleRenderCall();
}
