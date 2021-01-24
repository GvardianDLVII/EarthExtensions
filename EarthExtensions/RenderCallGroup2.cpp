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
	for (auto it = Offset.begin(); it != Offset.end(); ++it)
	{
		RenderPart(it->second, it->first);
		it->second = 0;
	}
}