#include "pch.h"
#include "UnitShadowRenderProxy.h"
#include "UnitShadowRenderCallGroup.h"

std::map<LPVOID, std::map<long, UnitShadowRenderCallGroup*>*> unitShadowCalls;

HRESULT UnitShadowRenderProxy::SetUnitShadowSquareTexture(LPVOID textureAddress, DWORD textureNum)
{
	UnitShadowRenderCallGroup::CurrentUnitShadowTextureAddress = textureAddress;
	UnitShadowRenderCallGroup::CurrentUnitShadowTextureNum = textureNum;
	return 0;
}

HRESULT UnitShadowRenderProxy::RegisterUnitShadowSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	auto textureAddressIterator = unitShadowCalls.find(UnitShadowRenderCallGroup::CurrentUnitShadowTextureAddress);
	std::map<long, UnitShadowRenderCallGroup*>* callGroup;
	if (textureAddressIterator == unitShadowCalls.end())
	{
		callGroup = new std::map<long, UnitShadowRenderCallGroup*>();
		unitShadowCalls[UnitShadowRenderCallGroup::CurrentUnitShadowTextureAddress] = callGroup;
	}
	else
	{
		callGroup = textureAddressIterator->second;
	}

	auto textureNumIterator = callGroup->find(UnitShadowRenderCallGroup::CurrentUnitShadowTextureNum);
	UnitShadowRenderCallGroup* callSubgroup;
	if (textureNumIterator == callGroup->end())
	{
		callSubgroup = new UnitShadowRenderCallGroup();
		callSubgroup->SetTextureAddress(UnitShadowRenderCallGroup::CurrentUnitShadowTextureAddress);
		(*callGroup)[UnitShadowRenderCallGroup::CurrentUnitShadowTextureNum] = callSubgroup;
	}
	else
	{
		callSubgroup = textureNumIterator->second;
	}

	callSubgroup->AddSquare(lpvVertices, lpwIndices);
	return 0;
}


HRESULT UnitShadowRenderProxy::CommitUnitShadow()
{
	for (auto it = unitShadowCalls.begin(); it != unitShadowCalls.end(); ++it)
	{
		for (auto it2 = it->second->begin(); it2 != it->second->end(); ++it2)
		{
			it2->second->Render(it2->first);
			it2->second->Clear();
		}
	}

	//call replaced asm code
	//005C9BCB 6A 01                push        1  
	//005C9BCD FF 15 D4 E2 9F 00    call        dword ptr ds : [9FE2D4h]
	typedef void(__stdcall* originalCall)(WORD param);

	void* originalFunctionPointer = (void*)(*((long*)0x009FE2D4));
	originalCall call = (originalCall)(originalFunctionPointer);
	call(1);
	return 0;
}