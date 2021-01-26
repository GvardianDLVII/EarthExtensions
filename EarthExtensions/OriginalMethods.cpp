#include "pch.h"
#include "OriginalMethods.h"

static byte TmpSetTextureCallBytes[] =
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
	TmpSetTextureCallBytes[6] = tnBytes[3];
	TmpSetTextureCallBytes[7] = tnBytes[2];
	TmpSetTextureCallBytes[8] = tnBytes[1];
	TmpSetTextureCallBytes[9] = tnBytes[0];
	TmpSetTextureCallBytes[11] = tuvBytes[3];
	TmpSetTextureCallBytes[12] = tuvBytes[2];
	TmpSetTextureCallBytes[13] = tuvBytes[1];
	TmpSetTextureCallBytes[14] = tuvBytes[0];
	TmpSetTextureCallBytes[18] = thBytes[3];
	TmpSetTextureCallBytes[19] = thBytes[2];
	TmpSetTextureCallBytes[20] = thBytes[1];
	TmpSetTextureCallBytes[21] = thBytes[0];
	TmpSetTextureCallBytes[25] = ocpBytes[3];
	TmpSetTextureCallBytes[26] = ocpBytes[2];
	TmpSetTextureCallBytes[27] = ocpBytes[1];
	TmpSetTextureCallBytes[28] = ocpBytes[0];
	typedef void(_stdcall* originalCall)(void);
	void* originalFunctionPointer = (void*)TmpSetTextureCallBytes;
	originalCall call = (originalCall)(originalFunctionPointer);
	call();
}


float GetCameraActorPosX()
{
	return *((float*)0x009FDA34);
}
float GetCameraActorPosY()
{
	return *((float*)0x009FDA38);
}
float GetCameraHeight()
{
	return *((float*)0x009FDA3C);
}