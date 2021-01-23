#include "pch.h"
#include "UnitShadowRenderCallGroup.h"

int UnitShadowRenderCallGroup::GetMaxOffset()
{
	return 100;
}
UnitShadowRenderCallGroup::UnitShadowRenderCallGroup(bool translucent) : RenderCallGroup2(translucent)
{
}