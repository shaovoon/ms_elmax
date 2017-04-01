#include "StdAfx.h"
#include "BaseConverter.h"
#include <climits>
#include <cfloat>
#include <sstream>
#include <iomanip>

using namespace Elmax;

BaseConverter::BaseConverter(void)
{
}

BaseConverter::~BaseConverter(void)
{
}

bool BaseConverter::SetBool(std::wstring& dest, bool val)
{
	if(val)
		dest = L"true";
	else
		dest = L"false";

	return true;
}

bool BaseConverter::SetString(std::wstring& dest, const std::wstring& val)
{
	dest = val;
	return true;
}

bool BaseConverter::SetString(std::wstring& dest, const std::string& val)
{
	if(val.size()<=0)
	{
		dest = L"";
		return false;
	}

	const size_t size = val.size()+1;
	wchar_t* pbuf = new wchar_t[size];

	if( !pbuf )
	{
		dest = L"";
		return false;
	}

	memset( pbuf, 0, size*sizeof(wchar_t) );

	size_t nConverted=0;
	errno_t nRet = mbstowcs_s(
		&nConverted,
		pbuf,
		size,
		val.c_str(),
		_TRUNCATE );


	if( 0 == nRet )
		dest = pbuf;

	delete [] pbuf;

	return true;
}

bool BaseConverter::SetHex(std::wstring& dest, unsigned int val, bool bAddPrefix)
{
	const int size = 30;
	wchar_t buf[size];
	memset( buf, 0, sizeof(buf) );
	errno_t nRet = _ultow_s( val, buf, size, 16 );
	//int nRet = swprintf_s(buf, L"%X", val);

	std::wstring dest2 = buf;
	if(bAddPrefix)
	{
		dest2 = L"0x";
		dest2 += buf;
	}

	// Convert to upper case
	std::wstring dest3 = L"";
	for (size_t i = 0; i < dest2.size(); ++i)
	{
		if(dest2.at(i)==L'a')
			dest3 += L'A';
		else if(dest2.at(i)==L'b')
			dest3 += L'B';
		else if(dest2.at(i)==L'c')
			dest3 += L'C';
		else if(dest2.at(i)==L'd')
			dest3 += L'D';
		else if(dest2.at(i)==L'e')
			dest3 += L'E';
		else if(dest2.at(i)==L'f')
			dest3 += L'F';
		else
			dest3 += dest2.at(i);
	}

	if( 0 == nRet )
	{
		dest = dest3;
		return true;
	}

	return false;
}

bool BaseConverter::CheckHexString(const std::wstring& str)
{
	for(size_t i=0; i<str.size(); ++i)
	{
		wchar_t ch = str.at(i);
		if(ch==L'A'||ch==L'B'||ch==L'C'||ch==L'D'||ch==L'E'||ch==L'F')
			continue;
		if(ch==L'a'||ch==L'b'||ch==L'c'||ch==L'd'||ch==L'e'||ch==L'f')
			continue;
		if(ch==L'0'||ch==L'1'||ch==L'2'||ch==L'3'||ch==L'4'||ch==L'5'||ch==L'6'||ch==L'7'||ch==L'8'||ch==L'9')
			continue;
		if(i==1 && (ch==L'x' || ch==L'X') )
			continue;

		return false;
	}

	return true;
}

bool BaseConverter::GetBool(const std::wstring& src, bool defaultVal, bool& val)
{
	if(src.size()<=0)
	{
		val = defaultVal;
		return false;
	}

	std::wstring src2 = L"";
	for(size_t i=0; i<src.size(); ++i)
		src2 += towlower(src.at(i));

	if(src2==L"true"||src2==L"yes"||src2==L"1"||src2==L"ok")
		val = true;
	else if(src2==L"false"||src2==L"no"||src2==L"0"||src2==L"cancel")
		val = false;
	else
	{
		val = defaultVal;
		return false;
	}

	return true;
}

bool BaseConverter::GetString(const std::wstring& src, const std::wstring& defaultVal, std::wstring& val)
{
	if(src.size()<=0)
	{
		val = defaultVal;
		return false;
	}

	val = src;

	return true;
}

bool BaseConverter::GetString(const std::wstring& src, const std::string& defaultVal, std::string& val)
{
	if(src.size()<=0)
	{
		val = defaultVal;
		return false;
	}

	char* pBuf = new char[src.size()+1];
	if( NULL == pBuf )
		return false;
	memset( pBuf, 0, src.size()+1 );
	size_t RetSize=0;
	errno_t err = wcstombs_s( &RetSize, pBuf, src.size()+1, src.c_str(), src.size()+1 );

	if( 0 != err )
	{
		delete [] pBuf;
		return false;
	}

	val=pBuf;
	delete [] pBuf;

	return true;
}

bool BaseConverter::SetGUID(std::wstring& dest, GUID val, bool bRemoveBraces)
{
	BSTR bstrGuid;
	StringFromCLSID(val, &bstrGuid);

	dest = (LPCWSTR)(bstrGuid);

	if(bRemoveBraces)
	{
		dest = dest.substr(1, 36);
	}

	// ensure memory is freed
	::CoTaskMemFree(bstrGuid);

	return true;
}

bool BaseConverter::GetGUID(const std::wstring& src, const GUID& defaultVal, GUID& val)
{
	std::wstring temp = src;
	if(src.length()==36)
	{
		temp = L"{";
		temp += src;
		temp += L"}";
	}

	bstr_t bstrGuid = (LPCWSTR)temp.c_str();
	HRESULT hr = CLSIDFromString(bstrGuid, &val);

	if(FAILED(hr))
	{
		val = defaultVal;
		return false;
	}

	return true;
}

bool BaseConverter::ReadHex(const std::wstring& src, unsigned int defaultVal, unsigned int& val)
{
	if(src.size()<=0||CheckHexString(src)==false)
	{
		val = defaultVal;
		return false;
	}

	std::wstring src2 = src;
	if (src.size() > 1 && src.at(0) == L'0' && (src.at(1) == L'X' || src.at(1) == L'x'))
	{
		std::wstring str2 = L"";
		for (size_t i = 2; i < src.size(); ++i)
			str2 += src[i];

		src2 = str2;
	}

	// Convert to lower case
	std::wstring src3 = L"";
	for (size_t i = 0; i < src2.size(); ++i)
	{
		if(src2.at(i)==L'A')
			src3 += L'a';
		else if(src2.at(i)==L'B')
			src3 += L'b';
		else if(src2.at(i)==L'C')
			src3 += L'c';
		else if(src2.at(i)==L'D')
			src3 += L'd';
		else if(src2.at(i)==L'E')
			src3 += L'e';
		else if(src2.at(i)==L'F')
			src3 += L'f';
		else
			src3 += src2.at(i);
	}


	std::wstringstream ss;
	ss << std::setbase(16) << src3;
	ss >> val;

	return true;
}

std::string BaseConverter::ConvToString(const std::wstring& text)
{
	std::string str = "";
	for(size_t i=0; i<text.length(); ++i)
	{
		str += (char)(text[i]);
	}

	return str;
}

std::wstring BaseConverter::ConvToString(const std::string& text)
{
	std::wstring str = L"";
	for(size_t i=0; i<text.length(); ++i)
	{
		str += (wchar_t)(text[i]);
	}

	return str;
}
