#include "pch.h"
#include "MeshRenderCallGroup.h"

MeshRenderCallGroup::MeshRenderCallGroup(bool translucent) : TriangleRenderCallGroup(translucent)
{
}
int MeshRenderCallGroup::GetMaxOffset()
{
	return 150;
}
