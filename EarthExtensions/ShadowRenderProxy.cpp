#include "pch.h"
#include "ShadowRenderProxy.h"
#include "UnitShadowRenderCallGroup.h"
#include "BuildingShadowRenderCallGroup.h"
#include <string>

std::map<LPVOID, std::map<long, UnitShadowRenderCallGroup*>*> unitShadowCalls;
std::map<std::string, BuildingShadowRenderCallGroup*> buildingShadowCalls;

HRESULT ShadowRenderProxy::SetUnitShadowSquareTexture(LPVOID textureAddress, DWORD textureNum)
{
	UnitShadowRenderCallGroup::CurrentUnitShadowTextureAddress = textureAddress;
	UnitShadowRenderCallGroup::CurrentUnitShadowTextureNum = textureNum;
	return 0;
}

HRESULT ShadowRenderProxy::RegisterUnitShadowSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
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


HRESULT ShadowRenderProxy::CommitUnitShadow()
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

static long callCount2 = 0;
HRESULT ShadowRenderProxy::SetBuildingShadowSquareTexture(long param0, long param1, long param2, long param3, long param4, long param5, long param6)
{
	BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[0] = param0;
	BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[1] = param1;
	BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[2] = param2;
	BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[3] = param3;
	BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[4] = param4;
	BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[5] = param5;
	BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[6] = param6;

	callCount2++;
	return BuildingShadowRenderCallGroup::CalculateTextureAddress(BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo);
}

HRESULT ShadowRenderProxy::RegisterBuildingShadowSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	std::string stringKey = std::to_string(BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[0])
		+ "_" + std::to_string(BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[1])
		+ "_" + std::to_string(BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[2])
		+ "_" + std::to_string(BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[3])
		+ "_" + std::to_string(BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[4])
		+ "_" + std::to_string(BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[5])
		+ "_" + std::to_string(BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[6]);
	auto textureAddressIterator = buildingShadowCalls.find(stringKey);
	BuildingShadowRenderCallGroup* callGroup;
	if (textureAddressIterator == buildingShadowCalls.end())
	{
		callGroup = new BuildingShadowRenderCallGroup();
		callGroup->SetTextureInfoParams(BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo);
		buildingShadowCalls[stringKey] = callGroup;
	}
	else
	{
		callGroup = textureAddressIterator->second;
	}

	callGroup->AddSquare(lpvVertices, lpwIndices);
	return 0;
}


HRESULT ShadowRenderProxy::CommitBuildingShadow()
{
	for (auto it = buildingShadowCalls.begin(); it != buildingShadowCalls.end(); ++it)
	{
		it->second->Render(0);
		it->second->Clear();
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