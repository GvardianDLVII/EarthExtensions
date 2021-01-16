#include "pch.h"
#include "RenderCallGroup.h"

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

IDirect3DDevice3* RenderCallGroup::GetD3DDevice()
{
	return *((IDirect3DDevice3**)0x009FBC24);
}

void RenderCallGroup::CallOriginalSetTexture(DWORD texturePartNum, DWORD textureUnknownValue)
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
	proxyCall[4] = tnBytes[3];
	proxyCall[5] = tnBytes[2];
	proxyCall[6] = tnBytes[1];
	proxyCall[7] = tnBytes[0];
	proxyCall[9] = tuvBytes[3];
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

void RenderCallGroup::RenderPart(long offset, DWORD texturePartNum, DWORD textureUnknownValue)
{
	CallOriginalSetTexture(texturePartNum, textureUnknownValue);
	GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_TLVERTEX, (LPVOID)VertexBuffer[textureUnknownValue], offset * 4, IndexBuffer[textureUnknownValue], offset * 6, 0);
}
void RenderCallGroup::AddSquare(D3DVERTEX* vertices, LPWORD indices)
{
	std::map<long, D3DVERTEX*>::iterator it = VertexBuffer.find(GetCurrentTextureUnknownValue());
	if (it == VertexBuffer.end())
	{
		D3DVERTEX* bufferedVeritices = new D3DVERTEX[GetMaxOffset() * 4];
		LPWORD bufferedIndices = new WORD[GetMaxOffset() * 6];
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
	if (currentOffset == GetMaxOffset())
	{
		RenderPart(currentOffset, GetCurrentTextureNum(), GetCurrentTextureUnknownValue());
		Offset[GetCurrentTextureUnknownValue()] = 0;
	}
}
void RenderCallGroup::Render(DWORD textureNum)
{
	for (auto it = Offset.begin(); it != Offset.end(); ++it)
	{
		RenderPart(it->second, textureNum, it->first);
	}
}
void RenderCallGroup::Clear()
{
	for (auto it = Offset.begin(); it != Offset.end(); ++it)
	{
		it->second = 0;
	}
}