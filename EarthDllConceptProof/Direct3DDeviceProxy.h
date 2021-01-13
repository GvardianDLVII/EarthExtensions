#pragma once
#include "pch.h"

HRESULT DrawIndexedPrimitive(IDirect3DDevice3* d3dDevice, LPVOID lpvVertices, LPWORD lpwIndices);
static LPVOID DrawIndexedPrimitiveAddress;