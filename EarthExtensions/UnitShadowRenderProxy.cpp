#include "pch.h"
#include "UnitShadowRenderProxy.h"
#include "UnitShadowRenderCallGroup.h"
#include "RenderManager.h"

UnitShadowRenderCallGroup* translucentUnitShadowCallGroup = new UnitShadowRenderCallGroup(true);
UnitShadowRenderCallGroup* standardUnitShadowCallGroup = new UnitShadowRenderCallGroup(false);

HRESULT UnitShadowRenderProxy::RegisterUnitShadowSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	if (RenderManager::GetTranslucentContext())
	{
		translucentUnitShadowCallGroup->AddSquare(lpvVertices, lpwIndices);
	}
	else
	{
		standardUnitShadowCallGroup->AddSquare(lpvVertices, lpwIndices);
	}

	return 0;
}


HRESULT UnitShadowRenderProxy::CommitUnitShadow()
{
	translucentUnitShadowCallGroup->Render();
	standardUnitShadowCallGroup->Render();
	return 0;
}