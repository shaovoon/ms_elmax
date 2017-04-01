#pragma once
#include "Element.h"
#include "UnicodeFile.h"
#include "ProcessingInstruction.h"

namespace Elmax
{
//! helper class for to call dom document's XPath methods
class Document
{
public:
	//! Non-default constructor
	Document(MSXML2::IXMLDOMDocumentPtr ptrDoc) : m_ptrDoc(ptrDoc) {};
	//! Destructors
	~Document(void);

	//! Get a list of elements by their tag name
	//!
	//! @param tagName is the tag name aka element name
	std::vector<Elmax::Element> GetElementsByTagName(const std::wstring& tagName);
	//! Get a list of elements by the XPath expression
	//! 
	//! @param xpath is the XPath expression
	std::vector<Elmax::Element> SelectNodes(const std::wstring& xpath);
	//! Get element by the XPath expression
	//! 
	//! @param xpath is the XPath expression
	Elmax::Element SelectSingleNode(const std::wstring& xpath);

	//! Save with the indentation and newlines
	//!
	//! @param file is file path
	//! @param xmlVersion is the xml version for the processing instruction, eg, L"1.0"
	//! @param utf8 specifies it should be saved in utf-8 or utf-16
	//! @param indent is indentation string used, eg L"\t"
	bool PrettySave(const std::wstring& file, const std::wstring& xmlVersion, bool utf8, const std::wstring& indent = L"    ");

	//! Save with the indentation and newlines
	//!
	//! @param file is file path
	//! @param procIntr specifies the processing instruction for the xml or none
	//! @param indent is indentation string used, eg L"\t"
	bool PrettySave(const std::wstring& file, ProcessingInstruction& procInstruction, const std::wstring& indent = L"    ");

private:
	//! Convert XMLNodeList to a vector of Element
	//! 
	//! @param pList is a smart pointer to IXMLNodeList
	//! @param vec is the returned vector of elements
	void ConvNodeListToVector(MSXML2::IXMLDOMNodeListPtr pList, std::vector<Elmax::Element>& vec);

	//! Write string to unicode file
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies the string should be written in utf-8 or utf-16
	//! @param str is the string to be written.
	static bool Write(CUnicodeFile& uf, bool utf8, const std::wstring& str);

	//! Write newline to unicode file
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies the string should be written in utf-8 or utf-16
	static bool WriteNewLine(CUnicodeFile& uf, bool utf8);

	//! Write indentation to unicode file
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param indent is indentation string used, eg L"\t"
	static bool WriteIndent(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent);

	//! Write start element (eg, <element>) to unicode file
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param elementName is the element name
	//! @param indent is indentation string used, eg L"\t"
	static bool WriteStartElement(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& elementName, const std::wstring& indent);

	//! Write start element (eg, <element>) to unicode file (without the newline at the beginning)
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param elementName is the element name
	//! @param indent is indentation string used, eg L"\t"
	static bool WriteFirstStartElement(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& elementName, const std::wstring& indent);

	//! Write end element (eg, </element>) to unicode file
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param elementName is the element name
	//! @param indent is indentation string used, eg L"\t"
	static bool WriteEndElement(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& elementName, const std::wstring& indent);

	//! Traverse the tree recursively and write them to file.
	//!
	//! @param node is the xml tree node
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param indent is indentation string used, eg L"\t"
	static bool Traverse(MSXML2::IXMLDOMNodePtr& node, CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent);

	//! Traverse the tree recursively and write them to file (without the processing instruction)(for pretty save)
	//!
	//! @param node is the xml tree node
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param indent is indentation string used, eg L"\t"
	static bool TraverseWithoutProcessingInstruction(MSXML2::IXMLDOMNodePtr& node, CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent);

	//! Replace all the anchor string instance found in the fmtstr string with another string
	static std::wstring Replace( 
		const std::wstring& fmtstr, 
		const std::wstring& anchor,
		const std::wstring& replace );

	//! Escape the XML string(eg, L"<>" to L"&lt;&gt;"
	static std::wstring EscapeXML( 
		const std::wstring& fmtstr);

	//! Unescape the XML string(eg, L"&lt;&gt;" to L"<>"
	static std::wstring UnEscapeXML( 
		const std::wstring& fmtstr);


	//! Internal XML Document
	MSXML2::IXMLDOMDocumentPtr m_ptrDoc;
};


}
