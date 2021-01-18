#include "pch.h"
#include "BuildingShadowRenderCallGroup.h"

static long callCount = 0;
LPVOID BuildingShadowRenderCallGroup::GetTextureAddress()
{
	callCount++;
	DWORD textureAddressParam = CalculateTextureAddress(TextureInfoParams);
	return (LPVOID)0x00A41520;
	//return TextureInfoParams;
}
void BuildingShadowRenderCallGroup::SetTextureInfoParams(DWORD params[7])
{
	TextureInfoParams[0] = params[0];
	TextureInfoParams[1] = params[1];
	TextureInfoParams[2] = params[2];
	TextureInfoParams[3] = params[3];
	TextureInfoParams[4] = params[4];
	TextureInfoParams[5] = params[5];
	TextureInfoParams[6] = params[6];
}
int BuildingShadowRenderCallGroup::GetMaxOffset()
{
	return 3500;
}
DWORD BuildingShadowRenderCallGroup::GetCurrentTextureNum()
{
	return 0;
}
DWORD BuildingShadowRenderCallGroup::GetCurrentTextureUnknownValue()
{
	return 4096;
}
DWORD BuildingShadowRenderCallGroup::CurrentBuildingShadowTextureInfo[];

BuildingShadowRenderCallGroup::BuildingShadowRenderCallGroup()
{
}

byte shadowTextureProxyCall[] =
{
	0x55,									//push	ebp
	0x89, 0xE5,								//mov	ebp, esp
	0x68, 0x00, 0x00, 0x00, 0x00,			//push param6
	0x68, 0x00, 0x00, 0x00, 0x00,			//push param5
	0x68, 0x00, 0x00, 0x00, 0x00,			//push param4
	0x68, 0x00, 0x00, 0x00, 0x00,			//push param3
	0x68, 0x00, 0x00, 0x00, 0x00,			//push param2
	0x68, 0x00, 0x00, 0x00, 0x00,			//push param1
	0xB9, 0x00, 0x00, 0x00, 0x00,			//mov ecx, param0
	0xFF, 0x15, 0x00, 0x00, 0x00, 0x00,		//call	[originalCallPointer]
	0x89, 0xEC,								//mov	esp, ebp
	0x5D,									//pop	ebp
	0xC3									//ret
};

DWORD BuildingShadowRenderCallGroup::CalculateTextureAddress(DWORD params[])
{
	void* originalFunctionPointer = (void*)(0x00610340);
	byte bytes0[4];
	ToByteArray(params[0], bytes0);
	byte bytes1[4];
	ToByteArray(params[1], bytes1);
	byte bytes2[4];
	ToByteArray(params[2], bytes2);
	byte bytes3[4];
	ToByteArray(params[3], bytes3);
	byte bytes4[4];
	ToByteArray(params[4], bytes4);
	byte bytes5[4];
	ToByteArray(params[5], bytes5);
	byte bytes6[4];
	ToByteArray(params[6], bytes6);
	byte bytesOC[4];
	ToByteArray((long)(&originalFunctionPointer), bytesOC);

	shadowTextureProxyCall[4] = bytes6[3];
	shadowTextureProxyCall[5] = bytes6[2];
	shadowTextureProxyCall[6] = bytes6[1];
	shadowTextureProxyCall[7] = bytes6[0];
	shadowTextureProxyCall[9] = bytes5[3];
	shadowTextureProxyCall[10] = bytes5[2];
	shadowTextureProxyCall[11] = bytes5[1];
	shadowTextureProxyCall[12] = bytes5[0];
	shadowTextureProxyCall[14] = bytes4[3];
	shadowTextureProxyCall[15] = bytes4[2];
	shadowTextureProxyCall[16] = bytes4[1];
	shadowTextureProxyCall[17] = bytes4[0];
	shadowTextureProxyCall[19] = bytes3[3];
	shadowTextureProxyCall[20] = bytes3[2];
	shadowTextureProxyCall[21] = bytes3[1];
	shadowTextureProxyCall[22] = bytes3[0];
	shadowTextureProxyCall[24] = bytes2[3];
	shadowTextureProxyCall[25] = bytes2[2];
	shadowTextureProxyCall[26] = bytes2[1];
	shadowTextureProxyCall[27] = bytes2[0];
	shadowTextureProxyCall[29] = bytes1[3];
	shadowTextureProxyCall[30] = bytes1[2];
	shadowTextureProxyCall[31] = bytes1[1];
	shadowTextureProxyCall[32] = bytes1[0];
	shadowTextureProxyCall[34] = bytes0[3];
	shadowTextureProxyCall[35] = bytes0[2];
	shadowTextureProxyCall[36] = bytes0[1];
	shadowTextureProxyCall[37] = bytes0[0];
	shadowTextureProxyCall[40] = bytesOC[3];
	shadowTextureProxyCall[41] = bytesOC[2];
	shadowTextureProxyCall[42] = bytesOC[1];
	shadowTextureProxyCall[43] = bytesOC[0];

	typedef DWORD(_stdcall* originalCall)(void);
	originalCall call = (originalCall)((void*)shadowTextureProxyCall);
	return call();
}