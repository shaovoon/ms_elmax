#pragma once
#include "NewNode.h"
#include "UnicodeFile.h"
#include "ProcessingInstruction.h"

namespace Elmax
{

class NewElement : public NewNode
{
public:
	~NewElement(void);

	NewElement operator[](LPCWSTR name);
	NewElement operator[](LPCSTR name);

	bool Exists() { return GetPtr()!=NULL; }

	//! Copy constructor
	NewElement(const NewElement& other);
	//! Assignment operator
	NewElement& operator=(const NewElement& other);

	// Constructors
	NewElement();
	NewElement(const std::wstring& name);
	NewElement(const std::wstring& name, const std::wstring& sValue);
	NewElement(const std::wstring& name, NewNode& node1);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15);
	NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15, NewNode& node16);
#if (_MSC_VER >= 1700 )
	NewElement Add(auto func(NewElement& parent)->void)
	{
		func(*this);
		return *this;
	}
#endif
	NewElement Add(NewNode& node1);
	NewElement Add(NewNode& node1, NewNode& node2);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15);
	NewElement Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
		NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
		NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15, NewNode& node16);

	//! Save XML to file
	//!
	//! @param file is file path
	//! @param xmlVersion is the xml version for the processing instruction, eg, L"1.0"
	//! @param utf8 specifies it should be saved in utf-8 or utf-16
	//! @param indent is indentation string used, eg L"\t"
	//! @param discard specifies to delete all the tree nodes
	bool Save(const std::wstring& file, const std::wstring& xmlVersion, bool utf8, bool discard = true);
	//! Save XML to file
	//!
	//! @param file is file path
	//! @param xmlVersion is the xml version for the processing instruction, eg, L"1.0"
	//! @param utf8 specifies it should be saved in utf-8 or utf-16
	//! @param indent is indentation string used, eg L"\t"
	//! @param discard specifies to delete all the tree nodes
	bool Save(const std::wstring& file, ProcessingInstruction& procInstruction, bool discard = true);
	//! Save with the indentation and newlines
	//!
	//! @param file is file path
	//! @param xmlVersion is the xml version for the processing instruction, eg, L"1.0"
	//! @param utf8 specifies it should be saved in utf-8 or utf-16
	//! @param indent is indentation string used, eg L"\t"
	//! @param discard specifies to delete all the tree nodes
	bool PrettySave(const std::wstring& file, const std::wstring& xmlVersion, bool utf8, const std::wstring& indent = L"    ", bool discard = true);
	//! Save with the indentation and newlines
	//!
	//! @param file is file path
	//! @param xmlVersion is the xml version for the processing instruction, eg, L"1.0"
	//! @param utf8 specifies it should be saved in utf-8 or utf-16
	//! @param indent is indentation string used, eg L"\t"
	//! @param discard specifies to delete all the tree nodes
	bool PrettySave(const std::wstring& file, ProcessingInstruction& procInstruction, const std::wstring& indent = L"    ", bool discard = true);
	bool Append(NewTreeNode* child);

private:

	//! Find the child with this chained names (eg, L"MyElement|MyChild")
	NewElement Find(const std::wstring& names);
	//! Find the 1st child with this name
	NewElement FindFirstChild(const std::wstring& name);

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

	//! Write the first start element (eg, <element>) to unicode file (without the newline at the beginning)
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
	static bool Traverse(NewTreeNode& node, CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent);

	//! Traverse the tree recursively and write them to file (without the processing instruction)(for pretty save)
	//!
	//! @param node is the xml tree node
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param indent is indentation string used, eg L"\t"
	static bool TraverseWithoutProcessingInstruction(NewTreeNode& node, CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent);

	//! Write start element (eg, <element>) to unicode file without indentation.
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param elementName is the element name
	static bool WriteStartElement(CUnicodeFile& uf, bool utf8, const std::wstring& elementName);

	//! Write end element (eg, </element>) to unicode file without indentation.
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param elementName is the element name
	static bool WriteEndElement(CUnicodeFile& uf, bool utf8, const std::wstring& elementName);

	//! Traverse the tree recursively and write them to file without indentation.
	//!
	//! @param node is the xml tree node
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param indent is indentation string used, eg L"\t"
	static bool Traverse(NewTreeNode& node, CUnicodeFile& uf, bool utf8);

	//! Replace all the anchor string instance found in the fmtstr string with another string
	static std::wstring Replace( 
		const std::wstring& fmtstr, 
		const std::wstring& anchor,
		const std::wstring& replace );

	//! Escape the XML string(eg, L"<>" to L"&lt;&gt;"
	static std::wstring EscapeXML( 
		const std::wstring& fmtstr);

	static std::wstring UnescapeXML( 
		const std::wstring& fmtstr);

};

} // ns Elmax

