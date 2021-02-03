#include "pch.h"
#include "WaterRenderProxy.h"
#include "WaterRenderCallGroup.h"
#include "WaterGreenOverlayRenderCallGroup.h"

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

std::map<LPVOID, std::map<long, WaterGreenOverlayRenderCallGroup*>*> waterGreenOverlayCalls;

HRESULT WaterRenderProxy::SetWaterGreenOverlayTexture(LPVOID textureAddress, DWORD textureNum, DWORD textureUnknownValue)
{
	WaterGreenOverlayRenderCallGroup::CurrentWaterTextureAddress = textureAddress;
	WaterGreenOverlayRenderCallGroup::CurrentWaterTextureUnknownValue = textureUnknownValue;
	WaterGreenOverlayRenderCallGroup::CurrentWaterTextureNum = textureNum;
	return 0;
}

HRESULT WaterRenderProxy::RegisterWaterGreenOverlayTriangleRendering(D3DVERTEX* lpvVertices)
{
	auto textureAddressIterator = waterGreenOverlayCalls.find(WaterGreenOverlayRenderCallGroup::CurrentWaterTextureAddress);
	std::map<long, WaterGreenOverlayRenderCallGroup*>* callGroup;
	if (textureAddressIterator == waterGreenOverlayCalls.end())
	{
		callGroup = new std::map<long, WaterGreenOverlayRenderCallGroup*>();
		waterGreenOverlayCalls[WaterGreenOverlayRenderCallGroup::CurrentWaterTextureAddress] = callGroup;
	}
	else
	{
		callGroup = textureAddressIterator->second;
	}

	auto textureNumIterator = callGroup->find(WaterGreenOverlayRenderCallGroup::CurrentWaterTextureNum);
	WaterGreenOverlayRenderCallGroup* callSubgroup;
	if (textureNumIterator == callGroup->end())
	{
		callSubgroup = new WaterGreenOverlayRenderCallGroup(WaterGreenOverlayRenderCallGroup::CurrentWaterTextureNum, WaterGreenOverlayRenderCallGroup::CurrentWaterTextureAddress);
		(*callGroup)[WaterGreenOverlayRenderCallGroup::CurrentWaterTextureNum] = callSubgroup;
	}
	else
	{
		callSubgroup = textureNumIterator->second;
	}

	callSubgroup->AddTriangle(lpvVertices);
	return 0;
}


HRESULT WaterRenderProxy::CommitWater()
{
	for (auto it = waterCalls.begin(); it != waterCalls.end(); ++it)
	{
		it->second->Render();
	}
	for (auto it = waterGreenOverlayCalls.begin(); it != waterGreenOverlayCalls.end(); ++it)
	{
		for (auto it2 = it->second->begin(); it2 != it->second->end(); ++it2)
		{
			it2->second->Render();
		}
	}
	return 0;
}