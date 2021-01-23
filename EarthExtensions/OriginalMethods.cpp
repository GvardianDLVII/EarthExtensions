#include "pch.h"
#include "OriginalMethods.h"

byte TmpSetTextureCallBytes[] =
{
	0x55,									//push	ebp
	0x89, 0xE5,								//mov	ebp, esp
	0x56,									//push	esi
	0x57,									//push	edi
	0xBA, 0x00, 0x00, 0x00, 0x00,			//mov	edx, [textureNum]
	0xB9, 0x00, 0x00, 0x00, 0x00,			//mov	ecx, [textureUnknownValue]
	0x51,									//push	ecx,
	0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00,		//mov	ecx, [textureAddress]
	0x52,									//push	edx
	0xFF, 0x15, 0x00, 0x00, 0x00, 0x00,		//call	[originalCallPointer]
	0x5F,									//pop	edi
	0x5E,									//pop	esi
	0x5D,									//pop	ebp
	0xC3									//ret
};

void TmpSetTextureCall(LPVOID textureAddress, DWORD texturePartNum, DWORD textureUnknownValue)
{
	byte tnBytes[4];
	ToByteArray(texturePartNum, tnBytes);
	byte tuvBytes[4];
	ToByteArray(textureUnknownValue, tuvBytes);
	byte thBytes[4];
	ToByteArray((DWORD)textureAddress, thBytes);
	unsigned long originalCallPointer = 0x005F8430;
	byte ocpBytes[4];
	ToByteArray((ULONG)&originalCallPointer, ocpBytes);
	TmpSetTextureCallBytes[4] = tnBytes[3];
	TmpSetTextureCallBytes[5] = tnBytes[2];
	TmpSetTextureCallBytes[6] = tnBytes[1];
	TmpSetTextureCallBytes[7] = tnBytes[0];
	TmpSetTextureCallBytes[9] = tuvBytes[3];
	TmpSetTextureCallBytes[10] = tuvBytes[2];
	TmpSetTextureCallBytes[11] = tuvBytes[1];
	TmpSetTextureCallBytes[12] = tuvBytes[0];
	TmpSetTextureCallBytes[16] = thBytes[3];
	TmpSetTextureCallBytes[17] = thBytes[2];
	TmpSetTextureCallBytes[18] = thBytes[1];
	TmpSetTextureCallBytes[19] = thBytes[0];
	TmpSetTextureCallBytes[23] = ocpBytes[3];
	TmpSetTextureCallBytes[24] = ocpBytes[2];
	TmpSetTextureCallBytes[25] = ocpBytes[1];
	TmpSetTextureCallBytes[26] = ocpBytes[0];
	typedef void(_stdcall* originalCall)(void);
	void* originalFunctionPointer = (void*)TmpSetTextureCallBytes;
	originalCall call = (originalCall)(originalFunctionPointer);
	call();
}

IDirect3DDevice3* GetD3DDevice()
{
	return *((IDirect3DDevice3**)0x009FBC24);
}

void RevEng5C34F0(long arg1, LPDIRECT3DTEXTURE2 texture)
{
	GetD3DDevice()->SetTexture(0, texture);
	if (arg1 == 0x70)
	{
		GetD3DDevice()->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, 0);
		return;
	}
	GetD3DDevice()->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, 1);
	GetD3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, 4);
	GetD3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2);
	GetD3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, 0);
	GetD3DDevice()->SetRenderState(D3DRENDERSTATE_SRCBLEND, 5);
	GetD3DDevice()->SetRenderState(D3DRENDERSTATE_DESTBLEND, 6);
}