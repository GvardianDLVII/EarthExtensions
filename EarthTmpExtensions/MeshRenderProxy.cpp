#include "pch.h"
#include "MeshRenderProxy.h"
#include "MeshRenderCallGroup.h"

std::map<LPVOID, std::map<long,MeshRenderCallGroup*>*> meshCalls;

HRESULT MeshRenderProxy::SetMeshTexture(LPVOID textureAddress, DWORD textureNum)
{
	MeshRenderCallGroup::CurrentMeshTextureAddress = textureAddress;
	MeshRenderCallGroup::CurrentMeshTextureNum = textureNum;
	return 0;
}

HRESULT MeshRenderProxy::RegisterMeshTriangleRendering(D3DVERTEX* lpvVertices)
{
	auto textureAddressIterator = meshCalls.find(MeshRenderCallGroup::CurrentMeshTextureAddress);
	std::map<long, MeshRenderCallGroup*>* callGroup;
	if (textureAddressIterator == meshCalls.end())
	{
		callGroup = new std::map<long, MeshRenderCallGroup*>();
		meshCalls[MeshRenderCallGroup::CurrentMeshTextureAddress] = callGroup;
	}
	else
	{
		callGroup = textureAddressIterator->second;
	}

	auto textureNumIterator = callGroup->find(MeshRenderCallGroup::CurrentMeshTextureNum);
	MeshRenderCallGroup* callSubgroup;
	if (textureNumIterator == callGroup->end())
	{
		callSubgroup = new MeshRenderCallGroup(MeshRenderCallGroup::CurrentMeshTextureNum, MeshRenderCallGroup::CurrentMeshTextureAddress);
		(*callGroup)[MeshRenderCallGroup::CurrentMeshTextureNum] = callSubgroup;
	}
	else
	{
		callSubgroup = textureNumIterator->second;
	}

	callSubgroup->AddTriangle(lpvVertices);
	return 0;
}


HRESULT MeshRenderProxy::CommitMesh()
{
	for (auto it = meshCalls.rbegin(); it != meshCalls.rend(); ++it)
	{
		for (auto it2 = it->second->rbegin(); it2 != it->second->rend(); ++it2)
		{
			it2->second->Render();
		}
	}
	return 0;
}