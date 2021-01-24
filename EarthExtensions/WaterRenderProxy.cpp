#include "pch.h"
#include "RenderManager.h"
#include "WaterRenderProxy.h"
#include "WaterRenderCallGroup.h"

WaterRenderCallGroup* translucentWaterCallGroup = new WaterRenderCallGroup(true);
WaterRenderCallGroup* standardWaterCallGroup = new WaterRenderCallGroup(false);

HRESULT WaterRenderProxy::RegisterWaterTriangleRendering(D3DVERTEX* lpvVertices)
{
	if (RenderManager::GetTranslucentContext())
	{
		translucentWaterCallGroup->AddTriangle(lpvVertices);
	}
	else
	{
		standardWaterCallGroup->AddTriangle(lpvVertices);
	}
	
	return 0;
}


HRESULT WaterRenderProxy::CommitWater()
{
	translucentWaterCallGroup->Render();
	standardWaterCallGroup->Render();
	return 0;
}