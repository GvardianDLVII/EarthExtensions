#include "Utils.h"
#include "pch.h"

void ToByteArray(DWORD ulong, byte result[])
{
	result[0] = (byte)((ulong >> 24) & 0xFF);
	result[1] = (byte)((ulong >> 16) & 0xFF);
	result[2] = (byte)((ulong >> 8) & 0XFF);
	result[3] = (byte)(ulong & 0XFF);
}