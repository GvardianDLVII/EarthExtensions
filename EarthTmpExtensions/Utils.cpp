#include "Utils.h"
#include <algorithm> 
#include <cctype>
#include <locale>
#include "pch.h"

void ToByteArray(DWORD ulong, byte result[])
{
	result[0] = (byte)((ulong >> 24) & 0xFF);
	result[1] = (byte)((ulong >> 16) & 0xFF);
	result[2] = (byte)((ulong >> 8) & 0XFF);
	result[3] = (byte)(ulong & 0XFF);
}

void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
        }));
}

void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
        }).base(), s.end());
}

void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

std::string trim_copy(std::string s) {
    trim(s);
    return s;
}