#include "pch.h"
#include "WaterRenderCallGroup.h"

WaterRenderCallGroup::WaterRenderCallGroup(bool translucent) : TriangleRenderCallGroup(translucent)
{
}
int WaterRenderCallGroup::GetMaxOffset()
{
	return 1000;
}
