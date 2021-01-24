#include "pch.h"
#include "RenderCallGroup.h"
#include "RenderManager.h"
#include "OriginalMethods.h"

RenderCallGroup2::RenderCallGroup2(bool translucent)
{
	this->translucent = translucent;
}
void RenderCallGroup2::Render()
{
	for (auto it = ArrayIndices.begin(); it != ArrayIndices.end(); ++it)
	{
		RenderPart(it->second, (LPDIRECT3DTEXTURE2)(it->first));
		Offset[it->second] = 0;
	}
}