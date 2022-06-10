#include "StdAfx.h"
#include "StringUtils.h"
#include "..\\BaseConverter.h"

using namespace Elmax;
std::wstring ToStr(bool val)
{
	std::wstring dest;

	if(val)
		dest = L"true";
	else
		dest = L"false";

	return dest;
}

std::wstring ToStr(char val)
{
	std::wstring dest;

	dest = val;

	return dest;
}

std::wstring ToStr(short val)
{
	std::string temp = std::to_string(val);
	return BaseConverter::ConvToString(temp);
}

std::wstring ToStr(int val)
{
	std::string temp = std::to_string(val);
	return BaseConverter::ConvToString(temp);
}

std::wstring ToStr(__int64 val)
{
	std::string temp = std::to_string(val);
	return BaseConverter::ConvToString(temp);
}

std::wstring ToStr(unsigned char val)
{
	std::string temp = std::to_string(val);
	return BaseConverter::ConvToString(temp);
}

std::wstring ToStr(unsigned short val)
{
	std::string temp = std::to_string(val);
	return BaseConverter::ConvToString(temp);
}

std::wstring ToStr(unsigned int val)
{
	std::string temp = std::to_string(val);
	return BaseConverter::ConvToString(temp);
}

std::wstring ToStr(unsigned __int64 val)
{
	std::string temp = std::to_string(val);
	return BaseConverter::ConvToString(temp);
}

std::wstring ToStr(float val)
{
	std::string temp = std::to_string(val);
	return BaseConverter::ConvToString(temp);
}

std::wstring ToStr(double val)
{
	std::string temp = std::to_string(val);
	return BaseConverter::ConvToString(temp);
}
