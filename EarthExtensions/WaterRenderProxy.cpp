#include "pch.h"
#include "WaterRenderProxy.h"
#include "WaterRenderCallGroup.h"

std::map<DWORD, WaterRenderCallGroup*> waterCalls;

HRESULT WaterRenderProxy::SetWaterSquareTexture(DWORD textureNum, DWORD textureUnknownValue)
{
	WaterRenderCallGroup::CurrentWaterTextureUnknownValue = textureUnknownValue;
	WaterRenderCallGroup::CurrentWaterTextureNum = textureNum;
	return 0;
}

HRESULT WaterRenderProxy::RegisterWaterSquareRendering(D3DVERTEX* lpvVertices)
{
	auto it = waterCalls.find(WaterRenderCallGroup::CurrentWaterTextureNum);
	WaterRenderCallGroup* callGroup;
	if (it == waterCalls.end())
	{
		callGroup = new WaterRenderCallGroup();
		waterCalls[WaterRenderCallGroup::CurrentWaterTextureNum] = callGroup;
	}
	else
	{
		callGroup = it->second;
	}
	callGroup->AddSquare(lpvVertices);
	return 0;
}


HRESULT WaterRenderProxy::CommitWater()
{
	for (auto it = waterCalls.begin(); it != waterCalls.end(); ++it)
	{
		it->second->Render(it->first);
		it->second->Clear();
	}

	//005C9BCD FF 15 D4 E2 9F 00    call        dword ptr ds : [9FE2C0h]
	typedef void(__stdcall* originalCall)(void);

	void* originalFunctionPointer = (void*)(*((long*)0x009FE2C0));
	originalCall call = (originalCall)(originalFunctionPointer);
	call();
	return 0;
}