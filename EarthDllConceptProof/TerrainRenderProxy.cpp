#include "pch.h"
#include "TerrainRenderProxy.h"
#include <map>
#include <list>
#include "Utils.h"

DWORD CurrentGroundTextureNum;
DWORD CurrentGroundTextureUnknownValue;

byte proxyCall[] =
{
	0x55,									//push	ebp
	0x89, 0xE5,								//mov	ebp, esp
	0xBA, 0x00, 0x00, 0x00, 0x00,			//mov	edx, [textureNum]
	0xB9, 0x00, 0x00, 0x00, 0x00,			//mov	ecx, [textureUnknownValue]
	0x51,									//push	ecx,
	0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00,		//mov	ecx, [00A41550h]
	0x52,									//push	edx
	0xFF, 0x15, 0x00, 0x00, 0x00, 0x00,		//call	[originalCallPointer]
	0x89, 0xEC,								//mov	esp, ebp
	0x5D,									//pop	ebp
	0xC3									//ret
};

class RenderCallGroup
{
protected:
	const int maxOffset = 35;
	std::map<long, D3DVERTEX*> VertexBuffer;
	std::map<long, LPWORD> IndexBuffer;
	std::map<long, WORD> Offset;

	virtual LPVOID GetTextureAddress() = 0;
	virtual DWORD GetCurrentTextureNum() = 0;
	virtual DWORD GetCurrentTextureUnknownValue() = 0;

	IDirect3DDevice3* GetD3DDevice()
	{
		return *((IDirect3DDevice3**)0x009FBC24);
	}

	void CallOriginalSetTexture(DWORD texturePartNum, DWORD textureUnknownValue)
	{
		//Original call:
		//001C8C2F - A1 2C1AA500 			mov eax, [00A51A2C]
		//001C8C34 - 8B 55 FC				mov edx, [ebp - 04]
		//001C8C37 - 2B C8  				sub ecx, eax
		//001C8C39 - 51						push ecx
		//001C8C3A - 8B 0D 5015A400			mov ecx, [00A41550]
		//001C8C40 - 52						push edx
		//001C8C41 - E8 EAF70200			call 005F8430

		byte tnBytes[4];
		ToByteArray(texturePartNum, tnBytes);
		byte tuvBytes[4];
		ToByteArray(textureUnknownValue, tuvBytes);
		byte thBytes[4];
		ToByteArray((DWORD)GetTextureAddress(), thBytes);
		unsigned long originalCallPointer = 0x005F8430;
		byte ocpBytes[4];
		ToByteArray((ULONG)&originalCallPointer, ocpBytes);
		proxyCall[4]  = tnBytes[3];
		proxyCall[5]  = tnBytes[2];
		proxyCall[6]  = tnBytes[1];
		proxyCall[7]  = tnBytes[0];
		proxyCall[9]  = tuvBytes[3];
		proxyCall[10] = tuvBytes[2];
		proxyCall[11] = tuvBytes[1];
		proxyCall[12] = tuvBytes[0];
		proxyCall[16] = thBytes[3];
		proxyCall[17] = thBytes[2];
		proxyCall[18] = thBytes[1];
		proxyCall[19] = thBytes[0];
		proxyCall[23] = ocpBytes[3];
		proxyCall[24] = ocpBytes[2];
		proxyCall[25] = ocpBytes[1];
		proxyCall[26] = ocpBytes[0];
		typedef void(_stdcall* originalCall)(void);
		void* originalFunctionPointer = (void*)proxyCall;
		originalCall call = (originalCall)(originalFunctionPointer);
		call();
	}

	void RenderPart(long offset, DWORD texturePartNum, DWORD textureUnknownValue)
	{
		CallOriginalSetTexture(texturePartNum, textureUnknownValue);
		GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, (LPVOID)VertexBuffer[textureUnknownValue], offset * 4, IndexBuffer[textureUnknownValue], offset * 6, 0);
	}
public:
	void AddSquare(D3DVERTEX* vertices, LPWORD indices)
	{
		std::map<long, D3DVERTEX*>::iterator it = VertexBuffer.find(GetCurrentTextureUnknownValue());
		if (it == VertexBuffer.end())
		{
			D3DVERTEX* bufferedVeritices = new D3DVERTEX[maxOffset * 4];
			LPWORD bufferedIndices = new WORD[maxOffset * 6];
			VertexBuffer.insert(std::pair<long, D3DVERTEX*>(GetCurrentTextureUnknownValue(), bufferedVeritices));
			IndexBuffer.insert(std::pair<long, LPWORD>(GetCurrentTextureUnknownValue(), bufferedIndices));
		}
		WORD currentOffset = Offset[GetCurrentTextureUnknownValue()];
		memcpy(VertexBuffer[GetCurrentTextureUnknownValue()] + currentOffset * 4, vertices, 4 * sizeof(D3DVERTEX));
		LPWORD copiedIndices = IndexBuffer[GetCurrentTextureUnknownValue()];
		memcpy(copiedIndices + currentOffset * 6, indices, 6 * sizeof(WORD));
		for (int i = currentOffset * 6; i < (currentOffset + 1) * 6; i++)
		{
			copiedIndices[i] += currentOffset * 4;
		}
		currentOffset++;
		Offset[GetCurrentTextureUnknownValue()] = currentOffset;
		if (currentOffset == maxOffset)
		{
			RenderPart(currentOffset, CurrentGroundTextureNum, GetCurrentTextureUnknownValue());
			Offset[GetCurrentTextureUnknownValue()] = 0;
		}
	}
	void Render(DWORD textureNum)
	{
		for (auto it = Offset.begin(); it != Offset.end(); ++it)
		{
			RenderPart(it->second, textureNum, it->first);
		}
	}
	void Clear()
	{
		for (auto it = Offset.begin(); it != Offset.end(); ++it)
		{
			it->second = 0;
		}
	}
};

class GroundRenderCallGroup : public RenderCallGroup
{
protected:
	virtual LPVOID GetTextureAddress()
	{
		return (LPVOID)0x00A41550;
	}
	virtual DWORD GetCurrentTextureNum()
	{
		return CurrentGroundTextureNum;
	}
	virtual DWORD GetCurrentTextureUnknownValue()
	{
		return CurrentGroundTextureUnknownValue;
	}
public:
};

class ResourceRenderCallGroup : public RenderCallGroup
{
protected:
	virtual LPVOID GetTextureAddress()
	{
		return (LPVOID)0x00A4153C;
	}
	virtual DWORD GetCurrentTextureNum()
	{
		return 0;
	}
	virtual DWORD GetCurrentTextureUnknownValue()
	{
		return 4096;
	}
public:
};

GroundRenderCallGroup textureCalls[1024];

HRESULT TerrainRenderProxy::SetGroundSquareTexture(DWORD textureNum, DWORD textureSize)
{
	CurrentGroundTextureNum = textureNum;
	CurrentGroundTextureUnknownValue = textureSize;
	return 0;
}

HRESULT TerrainRenderProxy::RegisterGroundSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	textureCalls[CurrentGroundTextureNum].AddSquare(lpvVertices, lpwIndices);
	return 0;
}

ResourceRenderCallGroup resourceRenderCall;

HRESULT TerrainRenderProxy::RegisterResourceSquareRendering(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
{
	resourceRenderCall.AddSquare(lpvVertices, lpwIndices);
	return 0;
}

HRESULT TerrainRenderProxy::Commit()
{
	for (int i = 0; i < 1024; i++)
	{
		textureCalls[i].Render(i);
		textureCalls[i].Clear();
	}

	resourceRenderCall.Render(0);
	resourceRenderCall.Clear();

	//call replaced asm code
	//005C9BCB 6A 01                push        1  
	//005C9BCD FF 15 D4 E2 9F 00    call        dword ptr ds : [9FE2D4h]
	typedef void (__stdcall *originalCall)(WORD param);

	void* originalFunctionPointer = (void*)(*((long*)0x009FE2D4));
	originalCall call = (originalCall)(originalFunctionPointer);
	call(1);
	return 0;
}