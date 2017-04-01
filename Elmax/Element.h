#pragma once

#include <string>
#include <vector>
#include <map>
#include "Attribute.h"
#include "CData.h"
#include "Comment.h"
#include "BaseConverter.h"
#include "Date.h"
#include "DateAndTime.h"
#include <atlstr.h>
#include <functional>
#include "NewNode.h"

namespace Elmax
{

//! Contains information about xml element
class Element
{
public:
	//! Constructor
	Element(void);
	//! Non-default Constructor
	Element(
		MSXML2::IXMLDOMDocumentPtr ptrDoc, 
		MSXML2::IXMLDOMNodePtr ptrNode, 
		const std::wstring& wstrNonExistingParent, 
		const std::wstring& wstrName, 
		bool bValid,
		bool bRoot);
	//! Copy constructor
	Element(const Element& other);
#if _HAS_CPP0X
	//! Move constructor
	Element(Element&& other);
#endif // _HAS_CPP0X
	//! Assignment operator
	Element& operator=(const Element& other);
#if _HAS_CPP0X
	//! Move assignment operator
	Element& operator=(const Element&& other);
#endif // _HAS_CPP0X

	//! Destructor
	virtual ~Element(void);

	//! Set the internal document object
	void SetDomDoc(MSXML2::IXMLDOMDocumentPtr ptrDoc);
	//! Get the internal document object
	MSXML2::IXMLDOMDocumentPtr GetDomDoc();
	//! Set the internal node object
	void SetNode(MSXML2::IXMLDOMNodePtr ptrNode);
	//! Get the internal node object
	MSXML2::IXMLDOMNodePtr GetNode();
	//! Get the root name (to access the root)
	std::wstring GetRootName();
	//! Get the element name
	std::wstring GetName() { return m_strName; }

	//! Returns true if the attribute with the name exists.
	bool Exists() const;
	//! Create this element with this optional namespaceUri, if not exists
	Element Create(const std::wstring& namespaceUri=L"");
	//! Always create this element with this optional namespaceUri
	Element CreateNew(const std::wstring& namespaceUri=L"");
	//! Add this node as child node
	bool AddNode(Element& node);
	//! Delete this child node
	bool RemoveNode(Element& node);
	//! Delete this node
	bool RemoveNode();
	//! Query Node by XPath
	Element SelectSingleNode(const std::wstring& szXPath);
	//! Query Nodes by XPath
	std::vector<Element> SelectNodes(const std::wstring& szXPath);

	//! type of element vector
	typedef std::vector< Element > collection_t;
	//! Get the collection of sibling elements with the same name
	collection_t AsCollection();
	//! Get the collection of sibling elements with the same name which satisfy the boolean predicate
	//! Note: template functions has to be in the header file, not cpp file.
	template<typename Predicate>
	collection_t AsCollection(Predicate pred)
	{
		if(!m_ptrNode || false == m_strNonExistingParent.empty() || false == m_bValid)
			throw std::runtime_error("Invalid Element");

		collection_t vec;
		ResolveNullNode(m_strName);
		MSXML2::IXMLDOMNodePtr parent = m_ptrNode->GetparentNode();
		if(!parent)
			return vec;
		MSXML2::IXMLDOMNodeListPtr pList = parent->GetchildNodes();

		vec.clear();
		for(long i=0; i<pList->length; ++i)
		{
			if(pList->item[i]->GetnodeType()==MSXML2::NODE_ELEMENT)
			{
				std::wstring name = (LPCWSTR)(pList->item[i]->nodeName);

				if(name==(LPCWSTR)m_ptrNode->nodeName)
				{
					Element ele(m_ptrDoc, pList->item[i], L"", m_strName, true, false);
					if(pred(ele))
						vec.push_back(ele);
				}
			}
		}

		return vec;
	}


	//! Get the collection of child elements with same name in vec
	collection_t GetChildren(const std::wstring& name);
	//! Get the collection of child elements with same name in vec, which satisfy the boolean predicate
	//! Note: template functions has to be in the header file, not cpp file.
	template<typename Predicate>
	collection_t Filter(const std::wstring& name, Predicate pred)
	{
		if(!m_ptrNode || false == m_strNonExistingParent.empty() || false == m_bValid)
			throw std::runtime_error("Invalid Element");

		collection_t vec;
		ResolveNullNode(m_strName);
		MSXML2::IXMLDOMNodeListPtr pList = m_ptrNode->GetchildNodes();

		vec.clear();
		if(pList)
		{
			for(long i=0; i<pList->length; ++i)
			{
				if(pList->item[i]->GetnodeType()==MSXML2::NODE_ELEMENT)
				{
					std::wstring nodename = (LPCWSTR)(pList->item[i]->nodeName);

					if(nodename==name)
					{
						Element ele(m_ptrDoc, pList->item[i], L"", name, true, false);
						if(pred(ele))
							vec.push_back(ele);
					}
				}
			}
		}

		return vec;
	};

	template<typename Predicate>
	collection_t Sort(const std::wstring& name, Predicate predSort) // Note: not an in-place sort!
	{
		if(!m_ptrNode || false == m_strNonExistingParent.empty() || false == m_bValid)
			throw std::runtime_error("Invalid Element");

		collection_t vec;
		ResolveNullNode(m_strName);
		MSXML2::IXMLDOMNodeListPtr pList = m_ptrNode->GetchildNodes();

		vec.clear();
		if(pList)
		{
			for(long i=0; i<pList->length; ++i)
			{
				if(pList->item[i]->GetnodeType()==MSXML2::NODE_ELEMENT)
				{
					std::wstring nodename = (LPCWSTR)(pList->item[i]->nodeName);

					if(nodename==name)
					{
						Element ele(m_ptrDoc, pList->item[i], L"", name, true, false);
						vec.push_back(ele);
					}
				}
			}
		}

		std::sort(vec.begin(), vec.end(), predSort);
		return vec;
	};

	template<typename Predicate>
	size_t Count(const std::wstring& name, Predicate pred) // for SQL Count function.
	{
		collection_t vec = Filter(name, pred);

		return vec.size();
	};

	typedef std::map< std::wstring, size_t > available_child_t;
	//! Query number of children for each Element name
	available_child_t QueryChildrenNum();

	// CData access methods
	//========================
	//! Add this CDataSection with data
	bool AddCData(const std::wstring& data);
	//! Delete this CDataSection at this index
	bool DeleteCData(size_t index);
	//! Delete this CDataSection at this index
	bool DeleteAllCData();
	//! Get this CDataSection collection
	std::vector<CData> GetCDataCollection();

	// Comment access methods
	//==========================
	//! Add this Comment object with this comment string
	bool AddComment(const std::wstring& comment);
	//! Delete this Comment at this index
	bool DeleteComment(size_t index);
	//! Delete this Comment at this index
	bool DeleteAllComments();
	//! Get this Comment collection
	std::vector<Comment> GetCommentCollection();

	// Base64 conversion methods
	//==========================
	//! Convert pSrc with this len(gth) to Base64 format
	static std::wstring ConvToBase64(const char* pSrc, int len);
	//! Convert pSrc with this len(gth) to wstrBase64Dest in Base64 format
	static bool ConvToBase64(const char* pSrc, int len, std::wstring& wstrBase64Dest);
	//! Convert wstrBase64Src from Base64 format to pDest with this len(gth)
	//! if pDest is null, len(gth) required will be returned
	static bool ConvFromBase64(const std::wstring& wstrBase64Src, char* pDest, int& len);

	//! Get the attribute with this attrName
	Elmax::Attribute Element::Attr(const std::wstring& attrName);
	//! Get the attribute with this ascii attrName
	Elmax::Attribute Element::Attr(const std::string& attrName);
	//! Get a list of attribute names.
	std::vector<std::wstring> GetAttrNames();
	//! Get a list of attributes.
	std::vector<Elmax::Attribute> GetAllAttr();


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
	//operator CString () const;
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

	Element operator[](LPCWSTR name);
	Element operator[](LPCSTR name);

	//! Set character value
	Element& operator=(char val);
	//! Set short value
	Element& operator=(short val);
	//! Set 32bit integer value
	Element& operator=(int val);
	//! Set 64bit integer value
	Element& operator=(__int64 val);
	//! Set unsigned character value
	Element& operator=(unsigned char val);
	//! Set unsigned short value
	Element& operator=(unsigned short val);
	//! Set unsigned 32bit integer value
	Element& operator=(unsigned int val);
	//! Set unsigned 64bit integer value
	Element& operator=(unsigned __int64 val);
	//! Set float value
	Element& operator=(float val);
	//! Set double value
	Element& operator=(double val);
	//! Set wide string value
	Element& operator=(const std::wstring& val);
	//! Set ascii string value
	Element& operator=(const std::string& val);
	//! Set constant CString value
	Element& operator=(const CString& val);
	//! Set constant wide character array
	Element& operator=(LPCWSTR val);
	//! Set constant ascii character array
	Element& operator=(LPCSTR val);
	//! Set constant GUID value
	Element& operator=(const GUID& val);
	//! Set constant Date value
	Element& operator=(const Elmax::Date& val);
	//! Set constant DateAndTime value
	Element& operator=(const Elmax::DateAndTime& val);

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
	//! Set the file contents into Base64 string value
	//!
	//! @param filepath is the source file to set from
	//! @param bSaveFilename indicates whether to save the filename in the FileName attribute
	//! @param bSaveFileLength indicates whether to save the file length in the FileLength attribute 
	//! because GetFileContents sometimes report a longer length which is not ideal if you need 
	//! to save the file to disk again
	bool SetFileContents(const std::wstring& filepath, bool bSaveFilename, bool bSaveFileLength);
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
	//! @param defaultVal is the default GUID value to use if src is invalid or empty
	GUID GetGUID(const GUID& defaultVal) const;
	//! Convert the string value into Date object if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default Date value to use if src is invalid or empty
	Elmax::Date GetDate(const Elmax::Date& defaultVal) const;
	//! Convert the string value into DateAndTime object if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default DateAndTime value to use if src is invalid or empty
	Elmax::DateAndTime GetDateTime(const Elmax::DateAndTime& defaultVal) const;
	//! Convert the Base64 string value into char array (remember to delete afterwards) if successful. If not successful, will return NULL
	//!
	//! @param filename is the filename saved in the FileName Attribute if available
	//! @param length is the file length of the char array returned.
	char* GetFileContents(std::wstring& filename, int& length);
	//! Convert the hexadecimal string value into unsigned integer value if successful. If not successful, will use the default value
	//!
	//! @param defaultVal is the default DateAndTime value to use if src is invalid or empty
	unsigned int ReadHex(unsigned int defaultVal) const;

	bool Add(NewNode& node1);
	bool Add(NewNode& node1, NewNode& node2);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15);
	bool Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15, NewNode& node16);


	__int64 Min(const std::wstring& elem, const std::wstring& attr = L"");
	__int64 Max(const std::wstring& elem, const std::wstring& attr = L"");
	__int64 Sum(const std::wstring& elem, const std::wstring& attr = L"");
	__int64 Avg(const std::wstring& elem, const std::wstring& attr = L"");

	float MinF(const std::wstring& elem, const std::wstring& attr = L"");
	float MaxF(const std::wstring& elem, const std::wstring& attr = L"");
	float SumF(const std::wstring& elem, const std::wstring& attr = L"");
	float AvgF(const std::wstring& elem, const std::wstring& attr = L"");

	double MinD(const std::wstring& elem, const std::wstring& attr = L"");
	double MaxD(const std::wstring& elem, const std::wstring& attr = L"");
	double SumD(const std::wstring& elem, const std::wstring& attr = L"");
	double AvgD(const std::wstring& elem, const std::wstring& attr = L"");

private:
	//! Split the str(ing) with delimiter "|/\\" into vec
	//!
	//! @param bMultipleParent returns true if there are more than 1 item in vec
	static bool SplitString(const std::wstring& str, std::vector<std::wstring>& vec, bool& bMultipleParent);
	//! Get Element with this str name
	Element GetNodeAt(const std::wstring& str);
	//! Try to resolve the null m_ptrNode problem
	void ResolveNullNode(const std::wstring& str);
	void ResolveNode(const std::wstring& str);
	//! Split the src with delimiter ":" into wstrNamespace and wstrName
	static bool SplitNamespace(const std::wstring& src, std::wstring& wstrName, std::wstring& wstrNamespace);
	//! Get the attribute value
	//!
	//! @param defaultVal is the default string value to use if src is invalid or empty
	//! @param val is the string value to be returned
	bool GetString(const std::wstring& defaultVal, std::wstring& val) const;

public:
	//! Attribute object
	Elmax::Attribute m_Attribute;

protected:
	//! type converter pointer
	BaseConverter* m_pIConverter;
	//! for returning wide raw array
	std::wstring m_strTemp;
	//! for returning narrow raw array
	std::string m_asciiStrTemp;
	//! Delimited string of non existing parent
	std::wstring m_strNonExistingParent;
	//! MS XML document object
	MSXML2::IXMLDOMDocumentPtr m_ptrDoc;
	//! MS XML node object
	MSXML2::IXMLDOMNodePtr m_ptrNode;
	//! Stores the deleted state
	bool m_bDeleted;
	//! Node name
	std::wstring m_strName;
	//! Stores the valid state
	bool m_bValid;
	//! State this node is root (is true if node 1st set with SetDocDom()
	bool m_bRoot;
public:
	static Element NullValue;

};



} // ns Elmax
