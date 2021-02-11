#include "pch.h"
#include "EffectsRenderCallGroup.h"

EffectsRenderCallGroup::EffectsRenderCallGroup(LPVOID textureAddress) : TriangleRenderCallGroup(0)
{
	TextureAddress = textureAddress;
}
LPVOID EffectsRenderCallGroup::GetTextureAddress()
{
	return &TextureAddress;
}
int EffectsRenderCallGroup::GetMaxOffset()
{
	return Configuration::GetMeshRenderBufferSize();
}
DWORD EffectsRenderCallGroup::GetCurrentTextureNum()
{
	return 0;
}
DWORD EffectsRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return 4096;
}
LPVOID EffectsRenderCallGroup::CurrentEffectTextureAddress;
