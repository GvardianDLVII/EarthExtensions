#include "pch.h"
#include "RenderCallGroup.h"

RenderCallGroup::RenderCallGroup(DWORD textureNum)
{
	this->textureNum = textureNum;
	lastIndex = 0;
}
DWORD RenderCallGroup::GetTextureNum()
{
	return textureNum;
}
void RenderCallGroup::Render()
{
	for (auto it = ArrayIndices.begin(); it != ArrayIndices.end(); ++it)
	{
		if (Offset[it->second] == 0)
			continue;
		RenderPart(it->second, it->first);
		Offset[it->second] = 0;
	}
}