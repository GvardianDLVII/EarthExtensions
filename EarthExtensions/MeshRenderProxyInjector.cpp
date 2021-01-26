#include "pch.h"
#include "MeshRenderProxyInjector.h"
#include "OriginalMethods.h"

MeshRenderProxy* MeshRenderProxyInjector::meshRenderer = 0;
bool MeshRenderProxyInjector::meshRenderContext = false;

HRESULT __stdcall MeshRenderProxyInjector::SetMeshSquareTextureWrapper(LPVOID textureAddress, DWORD textureNum)
{
	if (meshRenderContext)
	{
		return meshRenderer->SetMeshSquareTexture(textureAddress, textureNum);
	}
	else
	{
		TmpSetTextureCall(&textureAddress, textureNum, 4096);
		return 0;
	}
}
HRESULT __stdcall MeshRenderProxyInjector::RegisterMeshSquareRenderingWrapper(D3DVERTEX* lpvVertices, DWORD _indCount, DWORD _flags)
{
	if (meshRenderContext)
	{
		return meshRenderer->RegisterMeshSquareRendering(lpvVertices);
	}
	else //default render action
	{
		(*((IDirect3DDevice3**)0x009FBC24))->DrawPrimitive(D3DPT_TRIANGLELIST, 0x01C4, lpvVertices, 3, 0);
	}
}
void MeshRenderProxyInjector::SetMeshRenderContext(bool ctx)
{
	meshRenderContext = ctx;
}
void MeshRenderProxyInjector::HookSetMeshSquareTextureCall()
{
	const ULONG_PTR injectAddress = 0x005C31C5;
	void** proxyFunctionAddress = &SetMeshSquareTextureAddress;
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
void MeshRenderProxyInjector::HookRegisterMeshSquareRenderCall()
{
	const ULONG_PTR injectAddress = 0x005C32AD;
	void** proxyFunctionAddress = &RegisterMeshSquareRenderingAddress;
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

MeshRenderProxyInjector::MeshRenderProxyInjector(MeshRenderProxy* meshRenderer)
{
	this->meshRenderer = meshRenderer;
	SetMeshSquareTextureAddress = (LPVOID)((ULONG_PTR)SetMeshSquareTextureWrapper);
	RegisterMeshSquareRenderingAddress = (LPVOID)((ULONG_PTR)RegisterMeshSquareRenderingWrapper);
}
void MeshRenderProxyInjector::Inject()
{
	HookSetMeshSquareTextureCall();
	HookRegisterMeshSquareRenderCall();
}
