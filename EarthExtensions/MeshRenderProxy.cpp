#include "pch.h"
#include "MeshRenderProxy.h"
#include "MeshRenderCallGroup.h"

std::map<LPVOID, std::map<long,MeshRenderCallGroup*>*> meshCalls;

HRESULT MeshRenderProxy::SetMeshSquareTexture(LPVOID textureAddress, DWORD textureNum)
{
	MeshRenderCallGroup::CurrentMeshTextureAddress = textureAddress;
	MeshRenderCallGroup::CurrentMeshTextureNum = textureNum;
	return 0;
}

HRESULT MeshRenderProxy::RegisterMeshSquareRendering(D3DVERTEX* lpvVertices)
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
		callSubgroup = new MeshRenderCallGroup();
		callSubgroup->SetTextureAddress(MeshRenderCallGroup::CurrentMeshTextureAddress);
		(*callGroup)[MeshRenderCallGroup::CurrentMeshTextureNum] = callSubgroup;
	}
	else
	{
		callSubgroup = textureNumIterator->second;
	}

	callSubgroup->AddSquare(lpvVertices);
	return 0;
}


HRESULT MeshRenderProxy::CommitMesh()
{
	for (auto it = meshCalls.begin(); it != meshCalls.end(); ++it)
	{
		for (auto it2 = it->second->begin(); it2 != it->second->end(); ++it2)
		{
			it2->second->Render(it2->first);
			it2->second->Clear();
		}
	}
	return 0;
}