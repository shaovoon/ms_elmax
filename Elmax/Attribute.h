#pragma once

#include <string>
#include <vector>
#include "Date.h"
#include "DateAndTime.h"
#include "BaseConverter.h"
#include <atlstr.h>

namespace Elmax
{
//! Attribute access class (does not contain the MS XML attribute or the NamedNodeMap object)
class Attribute
{
public:
	//! Default Constructor
	Attribute();
	//! Non-default Constructor
	Attribute(
		MSXML2::IXMLDOMDocumentPtr& ptrDoc, 
		MSXML2::IXMLDOMNodePtr& ptrNode, 
		BaseConverter* pIConverter);
	//! Copy constructor
	Attribute(const Attribute& other);
#if _HAS_CPP0X
	//! Move constructor
	Attribute(Attribute&& other);
#endif // _HAS_CPP0X
	//! Assignment operator
	Attribute& operator=(const Attribute& other);
#if _HAS_CPP0X
	//! Move assignment operator
	Attribute& operator=(const Attribute&& other);
#endif // _HAS_CPP0X

	//! Destructor
	~Attribute(void);

	//! Returns true if the attribute with the name exists.
	bool Exists() const;

	std::wstring GetName() { return m_strAttrName; }

	//! Create this attribute with this optional namespaceUri
	bool Create(const std::wstring& namespaceUri=L"");
	
	//! Delete this attribute
	bool Delete();

	//! Set the data members
	void SetParam(
		MSXML2::IXMLDOMDocumentPtr& ptrDoc, 
		MSXML2::IXMLDOMNodePtr& ptrNode, 
		const std::wstring& wstrName);

	//! Get character value
	operator char () const;
	//! Get short value
	operator short () const;
	//! Get 32bit integer value
	operator int () const;
	//! Get 64bit integer value
	operator __int64 () const;
	//! Get unsigned character value
	operator unsigned char () const;
	//! Get unsigned short value
	operator unsigned short () const;
	//! Get unsigned 32bit integer value
	operator unsigned int () const;
	//! Get unsigned 64bit integer value
	operator unsigned __int64 () const;
	//! Get float value
	operator float () const;
	//! Get double value
	operator double () const;
	//! Get ascii string value
	operator std::string () const;
	//! Get wide string value
	operator std::wstring () const;
	//! Get constant ascii string value
	operator const std::string () const;
	//! Get constant wide string value
	operator const std::wstring () const;
	//! Get CString value
	operator const CString () const;
	//! Get constant wide character array
	operator LPCWSTR ();
	//! Get constant ascii character array
	operator LPCSTR ();
	//! Get GUID value
	operator GUID () const;
	//! Get Date value
	operator Elmax::Date () const;
	//! Get DateAndTime value
	operator Elmax::DateAndTime () const;

	//! Set character value
	void operator=(char val);
	//! Set short value
	void operator=(short val);
	//! Set 32bit integer value
	void operator=(int val);
	//! Set 64bit integer value
	void operator=(__int64 val);
	//! Set unsigned character value
	void operator=(unsigned char val);
	//! Set unsigned short value
	void operator=(unsigned short val);
	//! Set unsigned 32bit integer value
	void operator=(unsigned int val);
	//! Set unsigned 64bit integer value
	void operator=(unsigned __int64 val);
	//! Set float value
	void operator=(float val);
	//! Set double value
	void operator=(double val);
	//! Set wide string value
	void operator=(const std::wstring& val);
	//! Set ascii string value
	void operator=(const std::string& val);
	//! Set constant CString value
	void operator=(const CString& val);
	//! Set constant wide character array
	void operator=(LPCWSTR val);
	//! Set constant ascii character array
	void operator=(LPCSTR val);
	//! Set constant GUID value
	void operator=(const GUID& val);
	//! Set constant Date value
	void operator=(const Elmax::Date& val);
	//! Set constant DateAndTime value
	void operator=(const Elmax::DateAndTime& val);

	//! Set the boolean into string value
	//!
	//! @param val is the source boolean value to convert from
	bool SetBool(bool val);
	//! Set the character into string value
	//!
	//! @param val is the source character value to convert from
	bool SetChar(char val);
	//! Set the short integer into string value
	//!
	//! @param val is the source short integer value to convert from
	bool SetInt16(short val);
	//! Set the 32bit integer into string value
	//!
	//! @param val is the source 32bit integer value to convert from
	bool SetInt32(int val);
	//! Set the 64bit integer into string value
	//!
	//! @param val is the source 64bit integer value to convert from
	bool SetInt64(__int64 val);
	//! Set the unsigned character into string value
	//!
	//! @param val is the source unsigned character value to convert from
	bool SetUChar(unsigned char val);
	//! Set the unsigned short into string value
	//!
	//! @param val is the source unsigned short value to convert from
	bool SetUInt16(unsigned short val);
	//! Set the unsigned 32bit integer into string value
	//!
	//! @param val is the source unsigned 32bit integer value to convert from
	bool SetUInt32(unsigned int val);
	//! Set the unsigned 64bit integer into string value
	//!
	//! @param val is the source unsigned 64bit integer value to convert from
	bool SetUInt64(unsigned __int64 val);
	//! Set the float into string value
	//!
	//! @param val is the source float value to convert from
	bool SetFloat(float val);
	//! Set the double into string value
	//!
	//! @param val is the source double value to convert from
	bool SetDouble(double val);
	//! Set the wide string into string value
	//!
	//! @param val is the source wide string value to set from
	bool SetString(const std::wstring& val);
	//! Set the ascii string into string value
	//!
	//! @param val is the source ascii string value to set from
	bool SetString(const std::string& val);
	//! Set the CString into string value
	//!
	//! @param val is the source wide string value to set from
	bool SetCString(const CString& val);
	//! Set the GUID struct into string value
	//!
	//! @param val is the source GUID struct value to set from
	bool SetGUID(const GUID& val, bool bRemoveBraces=false);
	//! Set the Date into string value
	//!
	//! @param val is the source Date struct value to set from
	bool SetDate(const Elmax::Date& val);
	//! Set the DateAndTime into string value
	//!
	//! @param val is the source DateAndTime object value to set from
	bool SetDateTime(const Elmax::DateAndTime& val);
	//! Set the unsigned 32bit integer into hexadecimal string value
	//!
	//! @param val is the source unsigned 32bit integer value to convert from
	//! @param val bAddPrefix indicates whether to add the "0x" prefix
	bool SetHex(unsigned int val, bool bAddPrefix=false);
	//! Convert the string value into boolean if successful. If not successful, will use the default value
	//! ("true" or "yes" or "1" or "ok" get true value 
	//! while "false" or "no" or "0" or "cancel" get false value)
	//!
	//! @param defaultVal is the default boolean value to use if src is invalid or empty
	bool GetBool(bool defaultVal) const;
	//! Convert the string value into character if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default character value to use if src is invalid or empty
	char GetChar(char defaultVal) const;
	//! Convert the string value into short integer if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default short integer value to use if src is invalid or empty
	short GetInt16(short defaultVal) const;
	//! Convert the string value into 32bit integer if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default 32bit integer value to use if src is invalid or empty
	int GetInt32(int defaultVal) const;
	//! Convert the string value into 64bit integer if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default 64bit integer value to use if src is invalid or empty
	__int64 GetInt64(__int64 defaultVal) const;
	//! Convert the string value into unsigned character if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default unsigned character value to use if src is invalid or empty
	unsigned char GetUChar(unsigned char defaultVal) const;
	//! Convert the string value into unsigned short if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default unsigned short value to use if src is invalid or empty
	unsigned short GetUInt16(unsigned short defaultVal) const;
	//! Convert the string value into unsigned 32bit integer if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default unsigned 32bit integer value to use if src is invalid or empty
	unsigned int GetUInt32(unsigned int defaultVal) const;
	//! Convert the string value into unsigned 64bit integer if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default unsigned 64bit integer value to use if src is invalid or empty
	unsigned __int64 GetUInt64(unsigned __int64 defaultVal) const;
	//! Convert the string value into float if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default float value to use if src is invalid or empty
	float GetFloat(float defaultVal) const;
	//! Convert the string value into double if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default double value to use if src is invalid or empty
	double GetDouble(double defaultVal) const;
	//! Set the string value into wide string if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default wide string value to use if src is invalid or empty
	std::wstring GetString(const std::wstring& defaultVal) const;
	//! Convert the string value into ascii string if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default ascii string value to use if src is invalid or empty
	std::string GetString(const std::string& defaultVal) const;
	//! Set the CString value into wide string if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default wide string value to use if src is invalid or empty
	CString GetCString(const CString& defaultVal) const;
	//! Convert the string value into GUID if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default GUID string value to use if src is invalid or empty
	GUID GetGUID(const GUID& defaultVal) const;
	//! Convert the string value into Date object if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default Date value to use if src is invalid or empty
	Elmax::Date GetDate(const Elmax::Date& defaultVal) const;
	//! Convert the string value into DateAndTime object if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default DateAndTime value to use if src is invalid or empty
	Elmax::DateAndTime GetDateTime(const Elmax::DateAndTime& defaultVal) const;
	//! Convert the hexadecimal string value into unsigned integer value if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default DateAndTime value to use if src is invalid or empty
	unsigned int ReadHex(unsigned int defaultVal) const;

private:
	//! Get the attribute value
	//!
	//! @param defaultVal is the default string value to use if src is invalid or empty
	//! @param val is the string value to be returned
	bool GetString(const std::wstring& defaultVal, std::wstring& val) const;
	//! Get attribute with this name
	//!
	//! @param wstrName is attribute name to get
	//! @param wstrValue is the attribute value 
	//! @param bExists states if this attribute exists
	bool GetAttributeAt(const std::wstring& wstrName, std::wstring& wstrValue, bool& bExists) const;

private:
	//! for returning wide raw array
	std::wstring m_strTemp; 
	//! for returning narrow raw string
	std::string m_asciiStrTemp; 
	//! MS XML document object
	MSXML2::IXMLDOMDocumentPtr m_ptrDoc;
	//! MS XML node object
	MSXML2::IXMLDOMNodePtr m_ptrNode;
	//! Attribute name
	std::wstring m_strAttrName;
};

} // ns Elmax
