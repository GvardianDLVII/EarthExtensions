#pragma once
#include "pch.h"

class TerrainRenderProxy
{
private:
	IDirect3DDevice3* d3dDevice;
public:
	/// <summary>
	/// It is a replacement to a call to 0x005F8430 in TheMoonroject.exe. I'm not exactly sure what 0x005F8430 does.
	/// The body of 0x005F8430 is pretty large, and analyzing it in order to understand it, would be too expensive.
	/// This function is injected in place of a call from terrain rendering logic only, but 0x005F8430 is called from many places in code.
	/// This method is responsible for setting texture
	/// </summary>
	/// <param name="textureNum"></param>
	/// <param name="textureSize"></param>
	/// <returns></returns>
	HRESULT SetGroundSquareTexture(DWORD textureNum, DWORD textureSize);

	/// <summary>
	/// It is a replacement to a call to 0x005F8430 in TheMoonroject.exe. I'm not exactly sure what 0x005F8430 does.
	/// The body of 0x005F8430 is pretty large, and analyzing it in order to understand it, would be too expensive.
	/// This function is injected in place of a call from terrain rendering logic only, but 0x005F8430 is called from many places in code.
	/// This method is responsible for setting texture
	/// </summary>
	/// <param name="textureNum"></param>
	/// <param name="textureSize"></param>
	/// <returns></returns>
	HRESULT SetGreenSquareTexture(DWORD textureNum, DWORD textureSize);

	/// <summary>
	/// It replaces a single call to IDirect3DDevice::DrawIndexedPrimitive. The difference is, that it stacks the draw call in memory instead of calling renderer.
	/// The actual rendering is performed at the end, in Commit function
	/// </summary>
	/// <param name="lpvVertices"></param>
	/// <param name="lpwIndices"></param>
	/// <returns></returns>
	HRESULT RegisterGreenSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices);

	/// <summary>
	/// It is a replacement to a call to 0x005F8430 in TheMoonroject.exe. I'm not exactly sure what 0x005F8430 does.
	/// The body of 0x005F8430 is pretty large, and analyzing it in order to understand it, would be too expensive.
	/// This function is injected in place of a call from terrain rendering logic only, but 0x005F8430 is called from many places in code.
	/// This method is responsible for setting texture
	/// </summary>
	/// <param name="textureNum"></param>
	/// <param name="textureSize"></param>
	/// <returns></returns>
	HRESULT SetNavMeshSquareTexture(DWORD textureNum);

	/// <summary>
	/// It replaces a single call to IDirect3DDevice::DrawIndexedPrimitive. The difference is, that it stacks the draw call in memory instead of calling renderer.
	/// The actual rendering is performed at the end, in Commit function
	/// </summary>
	/// <param name="lpvVertices"></param>
	/// <param name="lpwIndices"></param>
	/// <returns></returns>
	HRESULT RegisterNavMeshSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices);

	/// <summary>
	/// It replaces a single call to IDirect3DDevice::DrawIndexedPrimitive. The difference is, that it stacks the draw call in memory instead of calling renderer.
	/// The actual rendering is performed at the end, in Commit function
	/// </summary>
	/// <param name="lpvVertices"></param>
	/// <param name="lpwIndices"></param>
	/// <returns></returns>
	HRESULT RegisterGroundSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices);

	/// <summary>
	/// It replaces a single call to IDirect3DDevice::DrawIndexedPrimitive. The difference is, that it stacks the draw call in memory instead of calling renderer.
	/// The actual rendering is performed at the end, in Commit function
	/// </summary>
	/// <param name="lpvVertices"></param>
	/// <param name="lpwIndices"></param>
	/// <returns></returns>
	HRESULT RegisterResourceSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices);

	/// <summary>
	/// Pushes to renderer all changes registered in current frame
	/// </summary>
	/// <param name="d3dDevice3"></param>
	/// <returns></returns>
	HRESULT Commit();

};