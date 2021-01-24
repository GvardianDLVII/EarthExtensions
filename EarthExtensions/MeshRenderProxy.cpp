#include "pch.h"
#include "RenderManager.h"
#include "MeshRenderProxy.h"
#include "MeshRenderCallGroup.h"

MeshRenderCallGroup* translucentMeshCallGroup = new MeshRenderCallGroup(true);
MeshRenderCallGroup* standardMeshCallGroup = new MeshRenderCallGroup(false);

HRESULT MeshRenderProxy::RegisterMeshTriangleRendering(D3DVERTEX* lpvVertices)
{
	if (RenderManager::GetTranslucentContext())
	{
		translucentMeshCallGroup->AddTriangle(lpvVertices);
	}
	else
	{
		standardMeshCallGroup->AddTriangle(lpvVertices);
	}

	return 0;
}


HRESULT MeshRenderProxy::CommitMesh()
{
	translucentMeshCallGroup->Render();
	standardMeshCallGroup->Render();
	return 0;
}