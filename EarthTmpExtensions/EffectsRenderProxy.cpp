#include "pch.h"
#include "EffectsRenderProxy.h"
#include "EffectsRenderCallGroup.h"

std::map<LPVOID, EffectsRenderCallGroup*> effectsCalls;

HRESULT EffectsRenderProxy::SetEffectsTexture(LPVOID textureAddress)
{
	EffectsRenderCallGroup::CurrentEffectTextureAddress = textureAddress;
	return 0;
}

HRESULT EffectsRenderProxy::RegisterEffectsTriangleRendering(D3DVERTEX* lpvVertices)
{
	auto textureAddressIterator = effectsCalls.find(EffectsRenderCallGroup::CurrentEffectTextureAddress);
	EffectsRenderCallGroup* callGroup;
	if (textureAddressIterator == effectsCalls.end())
	{
		callGroup = new EffectsRenderCallGroup(EffectsRenderCallGroup::CurrentEffectTextureAddress);
		effectsCalls[EffectsRenderCallGroup::CurrentEffectTextureAddress] = callGroup;
	}
	else
	{
		callGroup = textureAddressIterator->second;
	}

	callGroup->AddTriangle(lpvVertices);
	return 0;
}


HRESULT EffectsRenderProxy::CommitEffects()
{
	GetD3DDevice()->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, 0);
	for (auto it = effectsCalls.rbegin(); it != effectsCalls.rend(); ++it)
	{
		it->second->Render();
	}
	return 0;
}
