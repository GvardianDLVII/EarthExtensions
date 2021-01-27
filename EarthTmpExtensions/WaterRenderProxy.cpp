#include "pch.h"
#include "WaterRenderProxy.h"
#include "WaterRenderCallGroup.h"

std::map<DWORD, WaterRenderCallGroup*> waterCalls;

HRESULT WaterRenderProxy::SetWaterTexture(DWORD textureNum, DWORD textureUnknownValue)
{
	WaterRenderCallGroup::CurrentWaterTextureUnknownValue = textureUnknownValue;
	WaterRenderCallGroup::CurrentWaterTextureNum = textureNum;
	return 0;
}

HRESULT WaterRenderProxy::RegisterWaterTriangleRendering(D3DVERTEX* lpvVertices)
{
	auto it = waterCalls.find(WaterRenderCallGroup::CurrentWaterTextureNum);
	WaterRenderCallGroup* callGroup;
	if (it == waterCalls.end())
	{
		callGroup = new WaterRenderCallGroup(WaterRenderCallGroup::CurrentWaterTextureNum);
		waterCalls[WaterRenderCallGroup::CurrentWaterTextureNum] = callGroup;
	}
	else
	{
		callGroup = it->second;
	}
	callGroup->AddTriangle(lpvVertices);
	return 0;
}


HRESULT WaterRenderProxy::CommitWater()
{
	for (auto it = waterCalls.begin(); it != waterCalls.end(); ++it)
	{
		it->second->Render();
	}
	return 0;
}