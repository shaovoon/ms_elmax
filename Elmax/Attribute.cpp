#include "StdAfx.h"
#include "Attribute.h"
#include <boost/lexical_cast.hpp>
#include "BaseConverter.h"

using namespace Elmax;

// Non-default constructor
Attribute::Attribute()
{
}

// Non-default constructor
Attribute::Attribute(
	MSXML2::IXMLDOMDocumentPtr& ptrDoc, 
	MSXML2::IXMLDOMNodePtr& ptrNode, 
	BaseConverter* pIConverter)
: m_ptrDoc(ptrDoc)
, m_ptrNode(ptrNode)
{
}

// Copy constructor
Attribute::Attribute(const Attribute& other)
: m_strTemp(other.m_strTemp)
, m_asciiStrTemp(other.m_asciiStrTemp)
, m_ptrDoc(other.m_ptrDoc)
, m_ptrNode(other.m_ptrNode)
, m_strAttrName(other.m_strAttrName)
{

}

#if _HAS_CPP0X
// Move constructor
Attribute::Attribute(Attribute&& other)
: m_strTemp(std::move(other.m_strTemp))
, m_asciiStrTemp(std::move(other.m_asciiStrTemp))
, m_ptrDoc(other.m_ptrDoc)
, m_ptrNode(other.m_ptrNode)
, m_strAttrName(std::move(other.m_strAttrName))
{
}
#endif // _HAS_CPP0X

// Assignment operator
Attribute& Attribute::operator=(const Attribute& other)
{
	m_strTemp = other.m_strTemp;
	m_asciiStrTemp = other.m_asciiStrTemp;
	m_ptrDoc = other.m_ptrDoc;
	m_ptrNode = other.m_ptrNode;
	m_strAttrName = other.m_strAttrName;

	return *this;
}

#if _HAS_CPP0X
// Move assignment operator
Attribute& Attribute::operator=(const Attribute&& other)
{
	m_strTemp = std::move(other.m_strTemp);
	m_asciiStrTemp = std::move(other.m_asciiStrTemp);
	m_ptrDoc = other.m_ptrDoc;
	m_ptrNode = other.m_ptrNode;
	m_strAttrName = std::move(other.m_strAttrName);

	return *this;
}
#endif // _HAS_CPP0X

Attribute::~Attribute(void)
{
}

bool Attribute::GetAttributeAt(const std::wstring& wstrAttrName, std::wstring& wstrValue, bool& bExists) const
{
	bExists = false;
	if(m_ptrNode)
	{
		MSXML2::IXMLDOMNamedNodeMapPtr attrList = m_ptrNode->Getattributes();

		if(attrList)
		{
			for(long i=0; i<attrList->length; ++i)
			{
				std::wstring name = (LPCWSTR)(attrList->item[i]->GetnodeName());
				if(wstrAttrName==name)
				{
					wstrValue = (LPCWSTR)(attrList->item[i]->Gettext());
					bExists = true;
					return true;
				}
			}
		}
	}

	return false;
}

bool Attribute::Exists() const
{
	if(!m_ptrDoc||!m_ptrNode)
		return false;

	std::wstring wstrValue;
	bool bExists = false;
	GetAttributeAt(m_strAttrName, wstrValue, bExists);

	return bExists;
}

void Attribute::SetParam(
	MSXML2::IXMLDOMDocumentPtr& ptrDoc, 
	MSXML2::IXMLDOMNodePtr& ptrNode, 
	const std::wstring& wstrAttrName)
{
	m_ptrDoc = ptrDoc;
	m_ptrNode = ptrNode;
	m_strAttrName = wstrAttrName;
}


bool Attribute::Create(const std::wstring& namespaceUri)
{
	if(m_ptrDoc&&m_ptrNode)
	{
		bool bExists = false;
		std::wstring wstrValue;
		GetAttributeAt(m_strAttrName, wstrValue, bExists);
		if(false==bExists)
		{
			MSXML2::IXMLDOMNamedNodeMapPtr attrList = m_ptrNode->Getattributes();

			//MSXML2::IXMLDOMAttributePtr pAttr = m_ptrDoc->createAttribute(m_strAttrName.c_str());
			MSXML2::IXMLDOMAttributePtr pAttr = m_ptrDoc->createNode(MSXML2::NODE_ATTRIBUTE, m_strAttrName.c_str(), namespaceUri.c_str());

			if(attrList&&pAttr)
				attrList->setNamedItem(pAttr);

			return true;
		}
	}

	return false;
}

bool Attribute::Delete()
{
	if(m_ptrNode)
	{
		bool bExists = false;
		std::wstring wstrValue;
		GetAttributeAt(m_strAttrName, wstrValue, bExists);
		if(bExists)
		{
			MSXML2::IXMLDOMNamedNodeMapPtr attrList = m_ptrNode->Getattributes();

			if(attrList)
				attrList->removeNamedItem(m_strAttrName.c_str());
		}
		else
			return false;
	}
	else
		throw std::runtime_error("No valid node in this Attribute!");

	return true;
}

Attribute::operator char () const
{
	return GetChar('\0');
}

Attribute::operator short () const
{
	return GetInt16(0);
}

Attribute::operator int () const
{
	return GetInt32(0);
}

Attribute::operator __int64 () const
{
	return GetInt64(0L);
}

Attribute::operator unsigned char () const
{
	return GetUChar(0);
}

Attribute::operator unsigned short () const
{
	return GetUInt16(0);
}

Attribute::operator unsigned int () const
{
	return GetUInt32(0);
}

Attribute::operator unsigned __int64 () const
{
	return GetUInt64(0L);
}

Attribute::operator float () const
{
	return GetFloat(0.0f);
}

Attribute::operator double () const
{
	return GetDouble(0.0);
}

Attribute::operator std::string () const
{
	return GetString("");
}

Attribute::operator std::wstring () const
{
	return GetString(L"");
}

Attribute::operator const std::string () const
{
	return GetString("");
}

Attribute::operator const std::wstring () const
{
	return GetString(L"");
}

Attribute::operator const CString () const
{
	return GetCString(L"");
}

Attribute::operator LPCWSTR ()
{
	m_strTemp = GetString(L"");
	return m_strTemp.c_str();
}

Attribute::operator LPCSTR ()
{
	m_asciiStrTemp = GetString("");
	return m_asciiStrTemp.c_str();
}

Attribute::operator GUID () const
{
	GUID defaultGUID;
	memset(&defaultGUID, 0, sizeof(defaultGUID));
	return GetGUID(defaultGUID);
}

Attribute::operator Elmax::Date () const
{
	Elmax::Date date;
	return GetDate(date);
}

Attribute::operator Elmax::DateAndTime () const
{
	Elmax::DateAndTime datetime;
	return GetDateTime(datetime);
}

void Attribute::operator=(char val)
{
	SetChar(val);
}

void Attribute::operator=(short val)
{
	SetInt16(val);
}

void Attribute::operator=(int val)
{
	SetInt32(val);
}

void Attribute::operator=(__int64 val)
{
	SetInt64(val);
}

void Attribute::operator=(unsigned char val)
{
	SetUChar(val);
}

void Attribute::operator=(unsigned short val)
{
	SetUInt16(val);
}

void Attribute::operator=(unsigned int val)
{
	SetUInt32(val);
}

void Attribute::operator=(unsigned __int64 val)
{
	SetUInt64(val);
}

void Attribute::operator=(float val)
{
	SetFloat(val);
}

void Attribute::operator=(double val)
{
	SetDouble(val);
}

void Attribute::operator=(const std::wstring& val)
{
	SetString(val);
}

void Attribute::operator=(const std::string& val)
{
	SetString(val);
}

void Attribute::operator=(const CString& val)
{
	SetCString(val);
}

void Attribute::operator=(LPCWSTR val)
{
	SetString(std::wstring(val));
}

void Attribute::operator=(LPCSTR val)
{
	SetString(std::string(val));
}

void Attribute::operator=(const GUID& val)
{
	SetGUID(val);
}

void Attribute::operator=(const Elmax::Date& val)
{
	SetDate(val);
}

void Attribute::operator=(const Elmax::DateAndTime& val)
{
	SetDateTime(val);
}

bool Attribute::SetBool(bool val)
{
	std::wstring strDest;
	if( BaseConverter::SetBool(strDest, val) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Attribute::SetChar(char val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetInt16(short val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetInt32(int val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetInt64(__int64 val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetUChar(unsigned char val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetUInt16(unsigned short val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetUInt32(unsigned int val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetUInt64(unsigned __int64 val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetFloat(float val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetDouble(double val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetString(const std::wstring& val)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("Invalid element");

	bool bExists = false;
	std::wstring wstrValue;
	GetAttributeAt(m_strAttrName, wstrValue, bExists);
	if(false==bExists)
		Create();

	MSXML2::IXMLDOMNamedNodeMapPtr attrList = m_ptrNode->Getattributes();

	if(attrList)
	{
		for(long i=0; i<attrList->length; ++i)
		{
			std::wstring name = (LPCWSTR)(attrList->item[i]->GetnodeName());
			if(m_strAttrName==name)
			{
				attrList->item[i]->Puttext(val.c_str());
				return true;
			}
		}

		MSXML2::IXMLDOMAttributePtr pAttr = m_ptrDoc->createAttribute(m_strAttrName.c_str());

		if(attrList&&pAttr)
		{
			pAttr->Puttext(val.c_str());
			attrList->setNamedItem(pAttr);
			return true;
		}
	}

	return false;
}

bool Attribute::SetString(const std::string& val)
{
	std::wstring strDest;
	if( BaseConverter::SetString(strDest, val) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Attribute::SetCString(const CString& val)
{
	return SetString((LPCWSTR)(val));
}

bool Attribute::SetGUID(const GUID& val, bool bRemoveBraces)
{
	std::wstring strDest;
	if( BaseConverter::SetGUID(strDest, val, bRemoveBraces) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Attribute::SetDate(const Elmax::Date& val)
{
	std::wstring strDest = val.GetString();
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetDateTime(const Elmax::DateAndTime& val)
{
	std::wstring strDest = val.GetString();
	if(SetString(strDest))
		return true;

	return false;
}

bool Attribute::SetHex(unsigned int val, bool bAddPrefix)
{
	std::wstring strDest;
	if( BaseConverter::SetHex(strDest, val, bAddPrefix) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Attribute::GetString(const std::wstring& defaultVal, std::wstring& val) const
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("Invalid element!");

	std::wstring wstrValue;
	bool bExists = false;
	GetAttributeAt(m_strAttrName, wstrValue, bExists);
	if(false==bExists||wstrValue.empty())
	{
		val = defaultVal;
		return false;
	}

	return BaseConverter::GetString(wstrValue, defaultVal, val);
}

bool Attribute::GetBool(bool defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	bool val = defaultVal;
	BaseConverter::GetBool(src, defaultVal, val);
	return val;
}

char Attribute::GetChar(char defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	char val = defaultVal;
	try
	{
		val = boost::lexical_cast<char>(BaseConverter::ConvToString(src));
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

short Attribute::GetInt16(short defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	short val = defaultVal;
	try
	{
		val = boost::lexical_cast<short>(BaseConverter::ConvToString(src));
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

int Attribute::GetInt32(int defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	int val = defaultVal;
	try
	{
		val = boost::lexical_cast<int>(BaseConverter::ConvToString(src));
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

__int64 Attribute::GetInt64(__int64 defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	__int64 val = defaultVal;
	try
	{
		val = boost::lexical_cast<__int64>(BaseConverter::ConvToString(src));
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned char Attribute::GetUChar(unsigned char defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	unsigned char val = defaultVal;
	try
	{
		val = boost::lexical_cast<unsigned char>(BaseConverter::ConvToString(src));
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned short Attribute::GetUInt16(unsigned short defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	unsigned short val = defaultVal;
	try
	{
		val = boost::lexical_cast<unsigned short>(BaseConverter::ConvToString(src));
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned int Attribute::GetUInt32(unsigned int defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	unsigned int val = defaultVal;
	try
	{
		val = boost::lexical_cast<unsigned int>(BaseConverter::ConvToString(src));
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned __int64 Attribute::GetUInt64(unsigned __int64 defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	unsigned __int64 val = defaultVal;
	try
	{
		val = boost::lexical_cast<unsigned __int64>(BaseConverter::ConvToString(src));
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

float Attribute::GetFloat(float defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	float val = defaultVal;
	try
	{
		val = boost::lexical_cast<float>(BaseConverter::ConvToString(src));
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

double Attribute::GetDouble(double defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	double val = defaultVal;
	try
	{
		val = boost::lexical_cast<double>(BaseConverter::ConvToString(src));
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

std::wstring Attribute::GetString(const std::wstring& defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	std::wstring val = defaultVal;
	BaseConverter::GetString(src, defaultVal, val);
	return val;
}

std::string Attribute::GetString(const std::string& defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	std::string val = defaultVal;
	BaseConverter::GetString(src, defaultVal, val);
	return val;
}

CString Attribute::GetCString(const CString& defaultVal) const
{
	return GetString((LPCWSTR)(defaultVal)).c_str();
}

GUID Attribute::GetGUID(const GUID& defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	GUID val = defaultVal;
	BaseConverter::GetGUID(src, defaultVal, val);
	return val;
}

Elmax::Date Attribute::GetDate(const Elmax::Date& defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	Elmax::Date val;
	try
	{
		val.SetString(src);
	}
	catch (...)
	{
		return defaultVal;
	}
	return val;
}

Elmax::DateAndTime Attribute::GetDateTime(const Elmax::DateAndTime& defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	Elmax::DateAndTime val;
	try
	{
		val.SetString(src);
	}
	catch (...)
	{
		return defaultVal;
	}
	return val;
}

unsigned int Attribute::ReadHex(unsigned int defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	unsigned int val = defaultVal;
	BaseConverter::ReadHex(src, defaultVal, val);
	return val;
}
