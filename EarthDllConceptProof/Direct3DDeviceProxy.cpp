#include "pch.h"

const int DrawCounterMax = 1;
static int DrawCounter = 0;
static D3DVERTEX copiedVertices[4 * DrawCounterMax];
static WORD copiedIndices[6 * DrawCounterMax];

HRESULT DrawIndexedPrimitive(IDirect3DDevice3* d3dDevice, LPVOID lpvVertices, LPWORD lpwIndices)
{
	D3DVERTEX* vertices = (D3DVERTEX* )lpvVertices;
	LPWORD indices = lpwIndices;
	memcpy(copiedVertices + DrawCounter*4, vertices, 4 * sizeof(D3DVERTEX));
	memcpy(copiedIndices + DrawCounter*6, indices, 6 * sizeof(WORD));
	for (int i = DrawCounter * 6; i < (DrawCounter + 1) * 6; i++)
	{
		copiedIndices[i] += DrawCounter * 4;
	}
	DrawCounter++;
	if (DrawCounter == DrawCounterMax)
	{
		HRESULT r = d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, copiedVertices, 4 * DrawCounterMax, copiedIndices, 6 * DrawCounterMax, 0);
		DrawCounter = 0;
		return r;
	}
	else
	{
		return D3D_OK;
	}
	//HRESULT r = d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, lpvVertices, 4, lpwIndices, 6, 0);
	//return r;
}

static LPVOID DrawIndexedPrimitiveAddress;