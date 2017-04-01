#include "StdAfx.h"
#include "Document.h"
#include "UnicodeFile.h"

using namespace Elmax;

Document::~Document(void)
{
}

std::vector<Elmax::Element> Document::GetElementsByTagName(const std::wstring& tagName)
{
	if(m_ptrDoc==NULL)
		throw std::runtime_error("Invalid document");

	std::vector<Elmax::Element> vec;

	MSXML2::IXMLDOMNodeListPtr pList = m_ptrDoc->getElementsByTagName(bstr_t(tagName.c_str()));

	ConvNodeListToVector(pList, vec);

	return vec;
}

std::vector<Elmax::Element> Document::SelectNodes(const std::wstring& xpath)
{
	if(m_ptrDoc==NULL)
		throw std::runtime_error("Invalid document");

	std::vector<Elmax::Element> vec;

	MSXML2::IXMLDOMNodeListPtr pList = m_ptrDoc->selectNodes(bstr_t(xpath.c_str()));

	ConvNodeListToVector(pList, vec);

	return vec;
}

Elmax::Element Document::SelectSingleNode(const std::wstring& xpath)
{
	if(m_ptrDoc==NULL)
		throw std::runtime_error("Invalid document");

	MSXML2::IXMLDOMNodePtr node = m_ptrDoc->selectSingleNode(bstr_t(xpath.c_str()));

	if(node)
	{
		return Element(m_ptrDoc, node, L"", (LPCWSTR)(node->nodeName), true, false);
	}

	return Element();
}

void Document::ConvNodeListToVector(MSXML2::IXMLDOMNodeListPtr pList, std::vector<Elmax::Element>& vec)
{
	if(pList==NULL)
		return;

	for(long i=0; i<pList->length; ++i)
	{
		Element ele(m_ptrDoc, pList->item[i], L"", (LPCWSTR)(pList->item[i]->nodeName), true, false);
		vec.push_back(ele);
	}
}

bool Document::PrettySave(const std::wstring& file, const std::wstring& xmlVersion, bool utf8, const std::wstring& indent)
{
	if(!m_ptrDoc)
		return false;

	if(m_ptrDoc->documentElement==NULL)
		return false;

	CUnicodeFile uf;
	// open for writing
	if(utf8)
	{
		bool bRet = uf.Open( file.c_str(), L"wt" );
		if(bRet==false)
			return false;

		uf.WriteUtf8Bom();
	}
	else // unicode/utf-16
	{
		bool bRet = uf.Open( file.c_str(), L"wb" );
		if(bRet==false)
			return false;

		// this unicode file class will write utf 16 bom automatically.
		//uf.WriteUtf16Bom();
	}

	// write processing instruction

	std::wstring procInst;
	if(utf8)
		procInst = L"<?xml version=\"" + xmlVersion + L"\" encoding=\"UTF-8\"?>";
	else
		procInst = L"<?xml version=\"" + xmlVersion + L"\" encoding=\"UTF-16\"?>";

	Write(uf, utf8, procInst);

	MSXML2::IXMLDOMNodePtr node = m_ptrDoc->documentElement;

	Traverse(node, uf, utf8, 0, indent);

	uf.Flush();
	uf.Close();

	return true;
}

bool Document::PrettySave(const std::wstring& file, ProcessingInstruction& procInstruction, const std::wstring& indent)
{
	if(!m_ptrDoc)
		return false;

	if(m_ptrDoc->documentElement==NULL)
		return false;

	CUnicodeFile uf;
	bool utf8 = procInstruction.utf8;
	// open for writing
	if(utf8)
	{
		bool bRet = uf.Open( file.c_str(), L"wt" );
		if(bRet==false)
			return false;

		uf.WriteUtf8Bom();
	}
	else // unicode/utf-16
	{
		bool bRet = uf.Open( file.c_str(), L"wb" );
		if(bRet==false)
			return false;

		// this unicode file class will write utf 16 bom automatically.
		//uf.WriteUtf16Bom();
	}

	// write processing instruction

	std::wstring procInst;

	if(procInstruction.noProcessingInstruction==false)
	{
		procInst = procInstruction.ToString();
		Write(uf, utf8, procInst);
	}

	MSXML2::IXMLDOMNodePtr node = m_ptrDoc->documentElement;

	if(procInstruction.noProcessingInstruction)
	{
		TraverseWithoutProcessingInstruction(node, uf, utf8, 0, indent);
	}
	else
	{
		Traverse(node, uf, utf8, 0, indent);
	}

	uf.Flush();
	uf.Close();

	return true;
}

bool Document::Write(CUnicodeFile& uf, bool utf8, const std::wstring& str)
{
	if(utf8)
		uf.WriteUtf8(str);
	else
		uf.Write(str);

	return true;
}

bool Document::WriteNewLine(CUnicodeFile& uf, bool utf8)
{
	if(utf8)
		uf.WriteUtf8(L"\n");
	else
		uf.Write(L"\n");

	return true;
}

bool Document::WriteIndent(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent)
{
	if(utf8)
	{
		for(size_t i=0;i<cnt;++i)
			uf.WriteUtf8(indent);
	}
	else
	{
		for(size_t i=0;i<cnt;++i)
			uf.Write(indent);
	}
	return true;
}

bool Document::WriteStartElement(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& elementName, const std::wstring& indent)
{
	WriteNewLine(uf, utf8);
	WriteIndent(uf, utf8, cnt, indent);
	std::wstring str = L"<";
	Write(uf, utf8, str+elementName);
	return true;
}

bool Document::WriteFirstStartElement(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& elementName, const std::wstring& indent)
{
	WriteIndent(uf, utf8, cnt, indent);
	std::wstring str = L"<";
	Write(uf, utf8, str+elementName);
	return true;
}

bool Document::WriteEndElement(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& elementName, const std::wstring& indent)
{
	WriteIndent(uf, utf8, cnt, indent);
	std::wstring str = L"</";
	Write(uf, utf8, str+elementName+L">");
	return true;
}

bool Document::Traverse(MSXML2::IXMLDOMNodePtr& node, CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent)
{
	if(node->GetnodeType()==MSXML2::NODE_ELEMENT)
	{
		WriteStartElement(uf, utf8, cnt, (LPCWSTR)(node->nodeName), indent);
		MSXML2::IXMLDOMNamedNodeMapPtr attrList = node->attributes;
		if(!attrList)
		{
			Write(uf, utf8, L">");
		}
		else if(attrList->length<=0)
		{
			Write(uf, utf8, L">");
		}
		else
		{
			// write all the attributes of this element
			std::wstring str = L"";
			for(long i=0; i<attrList->length; ++i)
			{
				str += L" ";
				std::wstring name = (LPCWSTR)(attrList->item[i]->GetnodeName());
				str += name + L"=\"";
				std::wstring value = (LPCWSTR)(attrList->item[i]->Gettext());
				str += EscapeXML(value);
				str += L"\"";
			}
			Write(uf, utf8, str + L">");
		}

		bool textValueWritten = false;
		MSXML2::IXMLDOMNodeListPtr nodeList = node->childNodes;
		if(nodeList&&nodeList->length>0)
		{
			++cnt;
			for(long i=0;i<nodeList->length; ++i)
			{
				MSXML2::IXMLDOMNodePtr node1 = nodeList->item[i];
				if(node1->GetnodeType()==MSXML2::NODE_TEXT)
					textValueWritten = true;
				Traverse(node1, uf, utf8, cnt, indent);
			}

			--cnt;
		}
		if(textValueWritten)
		{
			WriteEndElement(uf, utf8, 0, (LPCWSTR)(node->nodeName), L"");
		}
		else
		{
			WriteNewLine(uf, utf8);
			WriteEndElement(uf, utf8, cnt, (LPCWSTR)(node->nodeName), indent);
		}
	}
	else if(node->GetnodeType()==MSXML2::NODE_TEXT)
	{
		MSXML2::IXMLDOMTextPtr text = node;
		if(text)
		{
			std::wstring str = EscapeXML((LPCWSTR)text->data);
			Write(uf, utf8, str);
		}
	}
	else if(node->GetnodeType()==MSXML2::NODE_COMMENT)
	{
		MSXML2::IXMLDOMCommentPtr comment = node;
		if(comment)
		{
			WriteNewLine(uf, utf8);
			WriteIndent(uf, utf8, cnt, indent);
			std::wstring str = L"<!--";
			str += (LPCWSTR)comment->data;
			str += L"-->";
			Write(uf, utf8, str);
		}
	}
	else if(node->GetnodeType()==MSXML2::NODE_CDATA_SECTION)
	{
		MSXML2::IXMLDOMCDATASectionPtr cdata = node;
		if(cdata)
		{
			WriteNewLine(uf, utf8);
			WriteIndent(uf, utf8, cnt, indent);
			std::wstring str = L"<![CDATA[";
			str += (LPCWSTR)cdata->data;
			str += L"]]>";
			Write(uf, utf8, str);
		}
	}
	return true;
}

bool Document::TraverseWithoutProcessingInstruction(MSXML2::IXMLDOMNodePtr& node, CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent)
{
	if(node->GetnodeType()==MSXML2::NODE_ELEMENT)
	{
		WriteFirstStartElement(uf, utf8, cnt, (LPCWSTR)(node->nodeName), indent);
		MSXML2::IXMLDOMNamedNodeMapPtr attrList = node->attributes;
		if(!attrList)
		{
			Write(uf, utf8, L">");
		}
		else if(attrList->length<=0)
		{
			Write(uf, utf8, L">");
		}
		else
		{
			// write all the attributes of this element
			std::wstring str = L"";
			for(long i=0; i<attrList->length; ++i)
			{
				str += L" ";
				std::wstring name = (LPCWSTR)(attrList->item[i]->GetnodeName());
				str += name + L"=\"";
				std::wstring value = (LPCWSTR)(attrList->item[i]->Gettext());
				str += EscapeXML(value);
				str += L"\"";
			}
			Write(uf, utf8, str + L">");
		}

		bool textValueWritten = false;
		MSXML2::IXMLDOMNodeListPtr nodeList = node->childNodes;
		if(nodeList&&nodeList->length>0)
		{
			++cnt;
			for(long i=0;i<nodeList->length; ++i)
			{
				MSXML2::IXMLDOMNodePtr node1 = nodeList->item[i];
				if(node1->GetnodeType()==MSXML2::NODE_TEXT)
					textValueWritten = true;
				Traverse(node1, uf, utf8, cnt, indent);
			}

			--cnt;
		}
		if(textValueWritten)
		{
			WriteEndElement(uf, utf8, 0, (LPCWSTR)(node->nodeName), L"");
		}
		else
		{
			WriteNewLine(uf, utf8);
			WriteEndElement(uf, utf8, cnt, (LPCWSTR)(node->nodeName), indent);
		}
	}
	else if(node->GetnodeType()==MSXML2::NODE_TEXT)
	{
		MSXML2::IXMLDOMTextPtr text = node;
		if(text)
		{
			std::wstring str = EscapeXML((LPCWSTR)text->data);
			Write(uf, utf8, str);
		}
	}
	else if(node->GetnodeType()==MSXML2::NODE_COMMENT)
	{
		MSXML2::IXMLDOMCommentPtr comment = node;
		if(comment)
		{
			WriteNewLine(uf, utf8);
			WriteIndent(uf, utf8, cnt, indent);
			std::wstring str = L"<!--";
			str += (LPCWSTR)comment->data;
			str += L"-->";
			Write(uf, utf8, str);
		}
	}
	else if(node->GetnodeType()==MSXML2::NODE_CDATA_SECTION)
	{
		MSXML2::IXMLDOMCDATASectionPtr cdata = node;
		if(cdata)
		{
			WriteNewLine(uf, utf8);
			WriteIndent(uf, utf8, cnt, indent);
			std::wstring str = L"<![CDATA[";
			str += (LPCWSTR)cdata->data;
			str += L"]]>";
			Write(uf, utf8, str);
		}
	}
	return true;
}

std::wstring Document::Replace( 
	const std::wstring& fmtstr, 
	const std::wstring& anchor,
	const std::wstring& replace )
{
	size_t pos = 0;

	std::wstring fmtstrReturn = fmtstr;

	while( std::wstring::npos != pos )
	{
		pos = fmtstrReturn.find( anchor, pos );

		if( std::wstring::npos != pos )
		{
			//fmtstr.replace( pos, 1, vs.at(i) );
			fmtstrReturn.erase( pos, anchor.size() );
			fmtstrReturn.insert( pos, replace );
			pos += replace.size();
		}
	}

	return fmtstrReturn;
}

std::wstring Document::EscapeXML( 
	const std::wstring& fmtstr)
{
	std::wstring fmtstr1 = Replace(fmtstr, L"&", L"&amp;");
	fmtstr1 = Replace(fmtstr1, L"\"", L"&quot;");
	fmtstr1 = Replace(fmtstr1, L"\'", L"&apos;");
	fmtstr1 = Replace(fmtstr1, L"<", L"&lt;");
	fmtstr1 = Replace(fmtstr1, L">", L"&gt;");

	return fmtstr1;
}

std::wstring Document::UnEscapeXML( 
	const std::wstring& fmtstr)
{
	std::wstring fmtstr1 = Replace(fmtstr, L"&quot;", L"\"");
	fmtstr1 = Replace(fmtstr1, L"&apos;", L"\'");
	fmtstr1 = Replace(fmtstr1, L"&lt;", L"<");
	fmtstr1 = Replace(fmtstr1, L"&gt;", L">");
	fmtstr1 = Replace(fmtstr1, L"&amp;", L"&");

	return fmtstr1;
}
