#include "StdAfx.h"
#include "Element.h"
#include "NewElement.h"
#include <boost/lexical_cast.hpp>

using namespace Elmax;

Element Element::NullValue;

Element::Element(void)
: m_strNonExistingParent(L"")
, m_bDeleted(false)
, m_bValid(true)
, m_bRoot(false)
{
}

// Non-default constructor
Element::Element(
	MSXML2::IXMLDOMDocumentPtr ptrDoc, 
	MSXML2::IXMLDOMNodePtr ptrNode, 
	const std::wstring& wstrNonExistingParent, 
	const std::wstring& wstrName, 
	bool bValid,
	bool bRoot)
: m_strNonExistingParent(wstrNonExistingParent)
, m_ptrDoc(ptrDoc)
, m_ptrNode(ptrNode)
, m_bDeleted(false)
, m_strName(wstrName)
, m_bValid(bValid)
, m_bRoot(bRoot)
{
}

// Copy constructor
Element::Element(const Element& other)
: m_strTemp(other.m_strTemp)
, m_asciiStrTemp(other.m_asciiStrTemp)
, m_strNonExistingParent(other.m_strNonExistingParent)
, m_ptrDoc(other.m_ptrDoc)
, m_ptrNode(other.m_ptrNode)
, m_bDeleted(other.m_bDeleted)
, m_strName(other.m_strName)
, m_bValid(other.m_bValid)
, m_Attribute(other.m_Attribute)
, m_bRoot(other.m_bRoot)
{

}

#if _HAS_CPP0X
// Move constructor
Element::Element(Element&& other)
: m_strTemp(std::move(other.m_strTemp))
, m_asciiStrTemp(std::move(other.m_asciiStrTemp))
, m_strNonExistingParent(std::move(other.m_strNonExistingParent))
, m_ptrDoc(other.m_ptrDoc)
, m_ptrNode(other.m_ptrNode)
, m_bDeleted(other.m_bDeleted)
, m_strName(std::move(other.m_strName))
, m_bValid(other.m_bValid)
, m_Attribute(other.m_Attribute)
, m_bRoot(other.m_bRoot)
{
}
#endif // _HAS_CPP0X

// Assignment operator
Element& Element::operator=(const Element& other)
{
	m_strTemp = other.m_strTemp;
	m_asciiStrTemp = other.m_asciiStrTemp;
	m_strNonExistingParent = other.m_strNonExistingParent;
	m_ptrDoc = other.m_ptrDoc;
	m_ptrNode = other.m_ptrNode;
	m_bDeleted = other.m_bDeleted;
	m_strName = other.m_strName;
	m_bValid = other.m_bValid;
	m_Attribute = other.m_Attribute;
	m_bRoot = other.m_bRoot;

	return *this;
}

#if _HAS_CPP0X
// Move assignment operator
Element& Element::operator=(const Element&& other)
{
	m_strTemp = std::move(other.m_strTemp);
	m_asciiStrTemp = std::move(other.m_asciiStrTemp);
	m_strNonExistingParent = std::move(other.m_strNonExistingParent);
	m_ptrDoc = other.m_ptrDoc;
	m_ptrNode = other.m_ptrNode;
	m_bDeleted = other.m_bDeleted;
	m_strName = std::move(other.m_strName);
	m_bValid = other.m_bValid;
	m_Attribute = other.m_Attribute;
	m_bRoot = other.m_bRoot;

	return *this;
}
#endif // _HAS_CPP0X

Element::~Element(void)
{
}

void Element::SetDomDoc(MSXML2::IXMLDOMDocumentPtr ptrDoc)
{
	m_ptrDoc = ptrDoc;
	m_bRoot = true;
	if(!m_ptrNode&&m_ptrDoc->documentElement)
	{
		m_ptrNode = (MSXML2::IXMLDOMNodePtr)(m_ptrDoc->documentElement);
		if(m_ptrNode)
		{
			m_strName = m_ptrNode->nodeName;
		}
	}
}

std::wstring Element::GetRootName()
{
	if(!m_ptrDoc)
		return L"";

	if(m_ptrDoc->documentElement==NULL)
		return L"";

	std::wstring rootName = (LPCWSTR)m_ptrDoc->documentElement->nodeName;

	return rootName;
}

MSXML2::IXMLDOMDocumentPtr Element::GetDomDoc()
{
	return m_ptrDoc;
}

void Element::SetNode(MSXML2::IXMLDOMNodePtr ptrNode)
{
	m_ptrNode = ptrNode;
}

MSXML2::IXMLDOMNodePtr Element::GetNode()
{
	return m_ptrNode;
}

void Element::ResolveNullNode(const std::wstring& str)
{
	if(m_ptrNode||m_ptrDoc->documentElement==NULL)
		return;

	using namespace std;
	bool bMultipleParent = false;
	vector<wstring> vec;
	std::wstring temp = str;
	wstring wstrNonExistingParent = L"";
	if(false==m_strNonExistingParent.empty())
	{
		temp = m_strNonExistingParent;
		temp += L"|";
		temp += m_strName;
	}
	else
	{
		temp = m_strName;
	}
	SplitString(temp, vec, bMultipleParent);

	if(bMultipleParent)
	{
		MSXML2::IXMLDOMNodePtr pSrc = m_ptrDoc->documentElement;
				
		for(size_t i=0; i<vec.size(); ++i)
		{
			// Get the collection from this node
			// If successful, assign the found node to this element
			// and find the next element.
			MSXML2::IXMLDOMNodeListPtr pList = pSrc->GetchildNodes();
			if(pList)
			{
				long len = pList->Getlength();
				for(long j=0; j<len; ++j)
				{
					MSXML2::IXMLDOMNodePtr pNode = pList->Getitem(j);
					if(pNode)
					{
						if(vec.at(i)==(LPCWSTR)pNode->nodeName)
						{
							pSrc = pNode;
							if(!m_ptrNode&&vec.at(vec.size()-1)==(LPCWSTR)pNode->baseName)
							{
								m_ptrNode = pNode;
								return;
							}
						}
					}
				}
			}
		}
	}
	else // if(bMultipleParent==false)
	{
		MSXML2::IXMLDOMNodePtr pSrc = m_ptrDoc->documentElement;
		if(m_strName==(LPCWSTR)pSrc->nodeName)
		{
			m_ptrNode = m_ptrDoc->documentElement;
			return;
		}
		MSXML2::IXMLDOMNodeListPtr pList = pSrc->GetchildNodes();
		if(pList)
		{
			long len = pList->Getlength();
			for(long j=0; j<len; ++j)
			{
				MSXML2::IXMLDOMNodePtr pNode = pList->Getitem(j);
				if(pNode)
				{
					if(!m_ptrNode)
					{
						if(str==(LPCWSTR)pNode->nodeName)
						{
							pSrc = pNode;
							if(!m_ptrNode&&m_strName==(LPCWSTR)pNode->baseName)
							{
								m_ptrNode = pNode;
								return;
							}
						}
					}
				}
			}
		}
	}
}

void Element::ResolveNode(const std::wstring& str)
{
	bool bRoot = false;
	if(!m_ptrNode)
	{
		m_ptrNode = m_ptrDoc->documentElement;
		if(!m_ptrNode)
			return;
		bRoot = true;
	}

	using namespace std;
	bool bMultipleParent = false;
	vector<wstring> vec;
	std::wstring temp = str;
	wstring wstrNonExistingParent = L"";
	if(false==m_strNonExistingParent.empty())
	{
		temp = m_strNonExistingParent;
		temp += L"|";
		temp += m_strName;
	}
	else
	{
		temp = m_strName;
	}
	SplitString(temp, vec, bMultipleParent);
	if(bMultipleParent)
	{
		m_strNonExistingParent = L"";
		for(size_t i=0; i<vec.size()-1; ++i)
		{
			m_strNonExistingParent += vec.at(i);
			if(i!=vec.size()-2)
				m_strNonExistingParent += L"|";
		}
		if(vec.size()>0)
			m_strName = vec.at(vec.size()-1);
	}

	return;
	if(bMultipleParent)
	{
		MSXML2::IXMLDOMNodePtr pSrc = m_ptrNode;

		size_t i=0;
		if(bRoot&&vec.size()>0&&vec.at(0)==(LPCWSTR)(pSrc->nodeName))
			i = 1;

		bool bFound = false;
		for(; i<vec.size(); ++i)
		{
			// Get the collection from this node
			// If successful, assign the found node to this element
			// and find the next element.
			MSXML2::IXMLDOMNodeListPtr pList = pSrc->GetchildNodes();
			if(pList)
			{
				long len = pList->Getlength();
				for(long j=0; j<len; ++j)
				{
					MSXML2::IXMLDOMNodePtr pNode = pList->Getitem(j);
					if(pNode)
					{
						if(vec.at(i)==(LPCWSTR)pNode->nodeName)
						{
							pSrc = pNode;
						}
					}
				}
				if(bFound==false)
					break;
			}
		}
		if(bFound)
		{
			if(pSrc)
				m_ptrNode = pSrc;
		}
	}
	else // if(bMultipleParent==false)
	{
		MSXML2::IXMLDOMNodePtr pSrc = m_ptrNode;
		if(!pSrc)
			return;
		if(bRoot&&vec.size()>0&&vec.at(0)==(LPCWSTR)(pSrc->nodeName))
			return;

		MSXML2::IXMLDOMNodeListPtr pList = pSrc->GetchildNodes();
		if(pList)
		{
			long len = pList->Getlength();
			for(long j=0; j<len; ++j)
			{
				MSXML2::IXMLDOMNodePtr pNode = pList->Getitem(j);
				if(pNode)
				{
					if(!m_ptrNode)
					{
						if(str==(LPCWSTR)pNode->nodeName)
						{
							pSrc = pNode;
							if(m_strName==(LPCWSTR)pNode->baseName)
							{
								m_ptrNode = pNode;
							}
						}
					}
				}
			}
		}
	}
}

Element Element::GetNodeAt(const std::wstring& str)
{
	ResolveNullNode(str);
	using namespace std;
	bool bMultipleParent = false;
	vector<wstring> vec;
	std::wstring temp = str;
	wstring wstrNonExistingParent = L"";
	if(false==m_strNonExistingParent.empty())
	{
		temp = m_strNonExistingParent;
		temp += L"|";
		if(m_strName.empty()==false)
		{
			temp += m_strName;
			temp += L"|";
		}
		temp += str;
	}
	else
	{
		if(m_ptrNode&&m_strName==(LPCWSTR)m_ptrNode->nodeName)
		{
			temp = str;
		}
		else
		{
			if(m_strName.empty()==false)
			{
				temp = m_strName;
				temp += L"|";
				temp += str;
			}
			else
				temp = str;
		}
	}
	SplitString(temp, vec, bMultipleParent);

	if(m_bRoot&&!m_ptrNode)
	{
		m_ptrNode = m_ptrDoc->documentElement;
		if(m_ptrNode && vec.size()>0 && vec.at(0)== (LPCWSTR)(m_ptrNode->nodeName))
		{
			m_strName = (LPCWSTR)(m_ptrNode->nodeName);
			//vector<wstring> vec2;
			//for(size_t i=1; i<vec.size();++i)
			//	vec2.push_back(vec.at(i));

			//vec = vec2;

			//if(vec.empty())
			//	bMultipleParent = false;
		}
	}

	if(m_ptrDoc||m_ptrNode)
	{
		if(m_strNonExistingParent.empty())
		{
			if(bMultipleParent)
			{
				if(m_ptrNode)
				{
					MSXML2::IXMLDOMNodePtr pSrc = m_ptrNode;
					bool found = false;
					size_t i=0;
					if(m_bRoot&&m_strName==(LPCWSTR)m_ptrNode->nodeName)
						i = 1;
					size_t nFound = i;
					for(; i<vec.size(); ++i)
					{
						// Get the collection from this node
						// If successful, assign the found node to this element
						// and find the next element.
						MSXML2::IXMLDOMNodeListPtr pList = pSrc->GetchildNodes();
						if(pList)
						{
							long len = pList->Getlength();
							for(long j=0; j<len; ++j)
							{
								MSXML2::IXMLDOMNodePtr pNode = pList->Getitem(j);
								if(pNode)
								{
									if(vec.at(i)==(LPCWSTR)pNode->nodeName)
									{
										pSrc = pNode;
										found = true;
										++nFound;
										break;
									}
								}
							}
							if(false==found)
							{
								for(;i<vec.size()-1;++i)
								{
									if(wstrNonExistingParent.empty()==false)
										wstrNonExistingParent += L"|";

									wstrNonExistingParent += vec.at(i);
								}

								if(vec.empty()==false)
									temp = vec.at(vec.size()-1);

								bool bRoot = m_bRoot;
								if(pSrc!=m_ptrNode)
									bRoot = false;

								return Element(m_ptrDoc, pSrc, wstrNonExistingParent, temp, false, bRoot);
							}
						}
					}
					if(found)
					{
						for(;i<vec.size()-1;++i)
						{
							if(wstrNonExistingParent.empty()==false)
								wstrNonExistingParent += L"|";

							wstrNonExistingParent += vec.at(i);
						}

						if(vec.empty()==false)
							temp = vec.at(vec.size()-1);

						bool bRoot = m_bRoot;
						if(pSrc!=m_ptrNode)
							bRoot = false;

						bool bValid = false;
						if(nFound==i)
							bValid = true;

						return Element(m_ptrDoc, pSrc, wstrNonExistingParent, temp, bValid, bRoot);
					}

				}
				else if(m_ptrDoc) // that is if(!m_ptrNode)
				{
					if(temp.find_first_of('|')!=-1||temp.find_first_of('\\')!=-1||temp.find_first_of('/')!=-1)
					{
						std::wstring tmp = L"";
						for(size_t i=0; i<vec.size()-1;++i)
						{
							tmp += vec.at(i);
							if(i!=vec.size()-2)
								tmp += L"|";
						}
						std::wstring name = L"";
						if(vec.size()>0)
							name = vec.at(vec.size()-1);

						return Element(m_ptrDoc, NULL, tmp, name, false, m_bRoot);
					}

					wstrNonExistingParent = m_strNonExistingParent;
					wstrNonExistingParent += L"|";
					wstrNonExistingParent += m_strName;

					if(wstrNonExistingParent==L"|")
						wstrNonExistingParent=L"";

					return Element(m_ptrDoc, NULL, wstrNonExistingParent, str, false, m_bRoot);
				}
			}
			else // if(bMultipleParent==false)
			{
				if(m_ptrNode)
				{
					if(m_bRoot&&str==(LPCWSTR)(m_ptrNode->nodeName))
						return Element(m_ptrDoc, m_ptrNode, wstrNonExistingParent, str, true, m_bRoot);

					MSXML2::IXMLDOMNodePtr pSrc = m_ptrNode;
					MSXML2::IXMLDOMNodeListPtr pList = pSrc->GetchildNodes();
					if(pList)
					{
						long len = pList->Getlength();
						bool found = false;
						for(long j=0; j<len; ++j)
						{
							MSXML2::IXMLDOMNodePtr pNode = pList->Getitem(j);
							if(pNode)
							{
								if(str==(LPCWSTR)pNode->nodeName)
								{
									pSrc = pNode;
									found = true;
									break;
								}
							}
						}
						if(false==found)
						{
							if(false==m_strNonExistingParent.empty())
							{
								wstrNonExistingParent = m_strNonExistingParent;
								wstrNonExistingParent += L"|";
								wstrNonExistingParent += m_strName;
							}
							else
								wstrNonExistingParent = L"";

							bool bRoot = m_bRoot;
							if(pSrc!=m_ptrNode)
								bRoot = false;
							
							return Element(m_ptrDoc, pSrc, wstrNonExistingParent, str, false, bRoot);
						}
						else // if(found)
						{
							bool bRoot = m_bRoot;
							if(pSrc!=m_ptrNode)
								bRoot = false;

							return Element(m_ptrDoc, pSrc, wstrNonExistingParent, str, true, bRoot);
						}
					}
				}
				else if(m_ptrDoc) // that is if(!m_ptrNode)
				{
					wstrNonExistingParent = m_strNonExistingParent;
					wstrNonExistingParent += L"|";
					wstrNonExistingParent += m_strName;

					if(wstrNonExistingParent==L"|")
						wstrNonExistingParent=L"";

					return Element(m_ptrDoc, m_ptrNode, wstrNonExistingParent, str, false, false); // svv
				}
			}
		}
		else // if(false == m_strNonExistingParent.empty())
		{
			for(size_t i=0;i<vec.size()-1;++i)
			{
				if(wstrNonExistingParent.empty()==false)
					wstrNonExistingParent += L"|";

				wstrNonExistingParent += vec.at(i);
			}

			return Element(m_ptrDoc, NULL, wstrNonExistingParent, str, false, m_bRoot);
		}
	}
	else
	{
		throw std::runtime_error("No valid xml document and node in this element!");
	}

	return Element();
}

bool Element::SplitString(const std::wstring& str, std::vector<std::wstring>& vec, bool& bMultipleParent)
{
	vec.clear();
	bMultipleParent = false;

	using namespace std;
	wstring temp = str;
	size_t size = temp.find_first_of(L'|');
	if(size!=wstring::npos)
	{
		bMultipleParent = true;
	}
	size = temp.find_first_of(L'\\');
	if(size!=wstring::npos)
	{
		bMultipleParent = true;
	}
	size = temp.find_first_of(L'/');
	if(size!=wstring::npos)
	{
		bMultipleParent = true;
	}
	if(bMultipleParent)
	{
		wchar_t seps[]   = L"|/\\";
		wchar_t *token = NULL;
		wchar_t *next_token = NULL;

		const size_t arrSize = temp.size()+1;
		wchar_t *p = new wchar_t[arrSize];
		if(!p)
			return false;
		memset(p, 0, arrSize * sizeof(wchar_t));
		wcscpy_s(p, arrSize, temp.c_str());
		token = wcstok_s(p, seps, &next_token );
		while( token != NULL )
		{
			vec.push_back(wstring(token));
			// Get next token
			token = wcstok_s( NULL, seps, &next_token );
		}
		delete [] p;
	}

	if(vec.empty()&&str.empty()==false)
		vec.push_back(str);

	return true;
}

bool Element::SplitNamespace(const std::wstring& src, std::wstring& wstrName, std::wstring& wstrNamespace)
{
	wstrName = src;
	wstrNamespace = L"";
	return false;
	bool bNamespace = false;
	using namespace std;
	wstring temp = src;
	size_t size = temp.find_first_of(L':');
	if(size!=wstring::npos)
	{
		bNamespace = true;
	}
	else
	{
		wstrName = src;
		return false;
	}
	if(bNamespace)
	{
		bool bFirstToken = true;
		wchar_t seps[]   = L":";
		wchar_t *token = NULL;
		wchar_t *next_token = NULL;

		const size_t arrSize = temp.size()+1;
		wchar_t *p = new wchar_t[arrSize];
		if(!p)
			return false;
		memset(p, 0, arrSize * sizeof(wchar_t));
		wcscpy_s(p, arrSize, temp.c_str());
		token = wcstok_s(p, seps, &next_token );
		while( token != NULL )
		{
			if(bFirstToken)
			{
				wstrNamespace = token;
				bFirstToken = false;
			}
			else
				wstrName = token;
			
			// Get next token
			token = wcstok_s( NULL, seps, &next_token );
		}
		delete [] p;
	}

	return true;
}

bool Element::Exists() const
{
	if(!m_ptrNode)
		return false;
	else if(false==m_bValid)
		return false;
	else if(m_strNonExistingParent.size()>0)
		return false;

	return true;
}

Element Element::Create(const std::wstring& namespaceUri)
{
	ResolveNode(m_strName);
	if(m_ptrNode)
	{
		if(m_strNonExistingParent.empty() && m_strName==(LPCWSTR)m_ptrNode->nodeName && m_bValid)
			return *this;
	}

	using namespace std;
	bool bMultipleParent = false;
	vector<wstring> vec;
	wstring wstrNonExistingParent = m_strNonExistingParent;
	wstrNonExistingParent += L"|";

	wstrNonExistingParent += m_strName;
	if(wstrNonExistingParent==L"|")
		wstrNonExistingParent=L"";

	SplitString(wstrNonExistingParent, vec, bMultipleParent);

	std::wstring namespaceUriTemp = L"";
	if(false==wstrNonExistingParent.empty())
	{
		if(m_ptrDoc&&m_ptrNode)
		{
			for(size_t i=0; i<vec.size(); ++i)
			{
				if(i==vec.size()-1)
					namespaceUriTemp = namespaceUri;
				MSXML2::IXMLDOMNodePtr pNew = m_ptrDoc->createNode(MSXML2::NODE_ELEMENT, vec.at(i).c_str(), namespaceUriTemp.c_str());

				if(pNew)
				{
					m_ptrNode = m_ptrNode->appendChild(pNew);
					m_bValid = true;
				}
			}
			m_bDeleted = false;
			m_strNonExistingParent = L"";
		}
		else if(m_ptrDoc&&!m_ptrNode)
		{
			for(size_t i=0; i<vec.size(); ++i)
			{
				if(i==vec.size()-1)
					namespaceUriTemp = namespaceUri;
				if(!m_ptrNode)
				{
					if(m_ptrDoc->documentElement==NULL)
					{
						m_ptrNode = m_ptrDoc->createNode(MSXML2::NODE_ELEMENT, vec.at(i).c_str(), namespaceUriTemp.c_str());
						m_ptrDoc->documentElement = static_cast<MSXML2::IXMLDOMElement*>(m_ptrNode.GetInterfacePtr());
						m_bValid = true;
					}
					else
					{
						m_ptrNode = m_ptrDoc->documentElement;
						m_bValid = true;
					}
				}
				else
				{
					MSXML2::IXMLDOMNodePtr pNew = m_ptrDoc->createNode(MSXML2::NODE_ELEMENT, vec.at(i).c_str(), namespaceUri.c_str());

					if(pNew&&m_ptrNode)
					{
						m_ptrNode = m_ptrNode->appendChild(pNew);
						m_bValid = true;
					}
				}

			}
			m_bDeleted = false;
			m_strNonExistingParent = L"";
		}
		else
			throw std::runtime_error("No valid xml document and node in this element!");
	}
	else // if(wstrNonExistingParent.empty())
	{
		if(m_ptrDoc&&m_ptrNode)
		{
			if(m_strName==(LPCWSTR)m_ptrNode->nodeName)
				return *this;
			else
			{
				MSXML2::IXMLDOMNodePtr pNew = m_ptrDoc->createNode(MSXML2::NODE_ELEMENT, m_strName.c_str(), namespaceUri.c_str());

				if(pNew)
				{
					m_ptrNode = m_ptrNode->appendChild(pNew);
					m_bValid = true;
					m_bDeleted = false;
					m_strNonExistingParent = L"";
				}
			}
		}
		else if(m_ptrDoc&&!m_ptrNode)
		{
			if(!m_ptrNode)
			{
				if(m_ptrDoc->documentElement==NULL)
				{
					m_ptrNode = m_ptrDoc->createNode(MSXML2::NODE_ELEMENT, m_strName.c_str(), namespaceUri.c_str());
					m_ptrDoc->documentElement = static_cast<MSXML2::IXMLDOMElement*>(m_ptrNode.GetInterfacePtr());
					m_bValid = true;
				}
				else
				{
					m_ptrNode = m_ptrDoc->documentElement;
					m_bValid = true;
				}
			}
			else
			{
				MSXML2::IXMLDOMNodePtr pNew = m_ptrDoc->createNode(MSXML2::NODE_ELEMENT, m_strName.c_str(), namespaceUri.c_str());

				if(pNew&&m_ptrNode)
				{
					m_ptrNode = m_ptrNode->appendChild(pNew);
					m_bValid = true;
				}
			}

			m_bDeleted = false;
			m_strNonExistingParent = L"";
		}
		else
			throw std::runtime_error("No valid xml document and node in this element!");
	}

	return *this;
}

Element Element::CreateNew(const std::wstring& namespaceUri)
{
	ResolveNode(m_strName);
	if(false==m_strNonExistingParent.empty()||false==m_bValid)
	{
		return Create(namespaceUri);
	}
	else // if(m_strNonExistingParent.empty())
	{
		if(m_ptrDoc&&m_ptrNode)
		{
			MSXML2::IXMLDOMNodePtr pNew = m_ptrDoc->createNode(MSXML2::NODE_ELEMENT, m_ptrNode->nodeName, namespaceUri.c_str());

			MSXML2::IXMLDOMNodePtr parent = m_ptrNode->GetparentNode();
			if(parent)
			{
				if (parent != m_ptrDoc || (parent == m_ptrDoc && !(m_ptrDoc->documentElement)))
				{
					m_ptrNode = parent->appendChild(pNew);
					m_bDeleted = false;
					m_bValid = true;

					return *this;
				}

				return Element();
			}
			else
				throw std::runtime_error("No valid parent found!");
		}
		else if(m_ptrDoc&&!m_ptrNode)
		{
			if(m_ptrDoc->documentElement==NULL)
			{
				m_ptrNode = m_ptrDoc->createNode(MSXML2::NODE_ELEMENT, m_strName.c_str(), namespaceUri.c_str());
				m_ptrDoc->documentElement = static_cast<MSXML2::IXMLDOMElement*>(m_ptrNode.GetInterfacePtr());
				m_bValid = true;
			}
			else
			{
				m_ptrNode = m_ptrDoc->documentElement;
				m_bValid = true;
			}

			m_bDeleted = false;
			return *this;
		}
		else
			throw std::runtime_error("No valid xml document and node in this element!");
	}

	// will not come here
	throw std::runtime_error("No valid xml document and node in this element!");
	return Element();
}

bool Element::AddNode(Element& node)
{
	if(false==m_strNonExistingParent.empty()||false==m_bValid)
	{
		throw std::runtime_error("Invalid element");
	}

	if(m_ptrDoc&&m_ptrNode)
	{
		if(node.m_ptrNode)
		{
			node.m_ptrNode = m_ptrNode->appendChild(node.m_ptrNode);
			node.m_ptrDoc = m_ptrDoc;
			node.m_bDeleted = false;
			return true;
		}
		else
			return false;
	}

	throw std::runtime_error("No valid xml document and node in this element!");

	return false;
}

bool Element::RemoveNode(Element& node)
{
	if(false==m_strNonExistingParent.empty()||false==m_bValid||node.m_bDeleted)
	{
		throw std::runtime_error("Invalid element");
	}

	if(m_ptrDoc&&m_ptrNode)
	{
		if(node.m_ptrNode)
		{
			node.m_ptrNode = m_ptrNode->removeChild(node.m_ptrNode);
			node.m_ptrDoc = NULL;
			node.m_bDeleted = true;
			return true;
		}
		else
			throw std::runtime_error("Invalid child node!");
	}

	throw std::runtime_error("No valid xml document and node in this element!");

	return false;
}

bool Element::RemoveNode()
{
	if(false==m_strNonExistingParent.empty()||false==m_bValid||m_bDeleted)
	{
		throw std::runtime_error("Invalid element");
	}

	if(m_ptrDoc&&m_ptrNode)
	{
		MSXML2::IXMLDOMNodePtr parent = m_ptrNode->GetparentNode();
		if(parent)
		{
			this->m_ptrNode = parent->removeChild(this->m_ptrNode);
			this->m_ptrDoc = NULL;
			this->m_bDeleted = true;
			return true;
		}
		else
			throw std::runtime_error("No valid parent!");
	}
	
	throw std::runtime_error("No valid xml document and node in this element!");
	return false;
}

Element::collection_t Element::AsCollection()
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
				vec.push_back(ele);
			}
		}
	}

	return vec;
}

Element::collection_t Element::GetChildren(const std::wstring& name)
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

	return vec;
}

Element::available_child_t Element::QueryChildrenNum()
{
	if(!m_ptrNode || false == m_strNonExistingParent.empty() || false == m_bValid)
		throw std::runtime_error("Invalid Element");

	Element::available_child_t children;
	MSXML2::IXMLDOMNodeListPtr pList = m_ptrNode->GetchildNodes();

	children.clear();
	for(long i=0; i<pList->length; ++i)
	{
		if(pList->item[i]->GetnodeType()==MSXML2::NODE_ELEMENT)
		{
			std::wstring nodename = (LPCWSTR)(pList->item[i]->nodeName);

			Element::available_child_t::iterator it = children.find(nodename);

			if(it!=children.end())
			{
				size_t n = it->second;
				++n;
				it->second = n;
			}
			else
				children.insert(std::make_pair(nodename,size_t(1)));
		}
	}

	return children;
}

Element::operator char () const
{
	return GetChar('\0');
}

Element::operator short () const
{
	return GetInt16(0);
}

Element::operator int () const
{
	return GetInt32(0);
}

Element::operator __int64 () const
{
	return GetInt64(0L);
}

Element::operator unsigned char () const
{
	return GetUChar(0);
}

Element::operator unsigned short () const
{
	return GetUInt16(0);
}

Element::operator unsigned int () const
{
	return GetUInt32(0);
}

Element::operator unsigned __int64 () const
{
	return GetUInt64(0L);
}

Element::operator float () const
{
	return GetFloat(0.0f);
}

Element::operator double () const
{
	return GetDouble(0.0);
}

Element::operator std::string () const
{
	return GetString("");
}

Element::operator std::wstring () const
{
	return GetString(L"");
}

//Element::operator CString () const
//{
//	return GetCString(L"");
//}

Element::operator const std::string () const
{
	return GetString("");
}

Element::operator const std::wstring () const
{
	return GetString(L"");
}

Element::operator const CString () const
{
	return GetCString(L"");
}

Element::operator LPCWSTR ()
{
	m_strTemp = GetString(L"");
	return m_strTemp.c_str();
}

Element::operator LPCSTR ()
{
	m_asciiStrTemp = GetString("");
	return m_asciiStrTemp.c_str();
}

Element::operator GUID () const
{
	GUID defaultGUID;
	memset(&defaultGUID, 0, sizeof(defaultGUID));
	return GetGUID(defaultGUID);
}

Element::operator Elmax::Date () const
{
	Elmax::Date date;
	return GetDate(date);
}

Element::operator Elmax::DateAndTime () const
{
	Elmax::DateAndTime datetime;
	return GetDateTime(datetime);
}

Element Element::operator[](LPCWSTR name)
{
	return GetNodeAt(name);
}

Element Element::operator[](LPCSTR name)
{
	// convert the ascii string to wide string
	std::wstring wname = L"";
	BaseConverter::SetString(wname, name);

	return GetNodeAt(wname);
}

Element& Element::operator=(char val)
{
	SetChar(val);
	return *this;
}

Element& Element::operator=(short val)
{
	SetInt16(val);
	return *this;
}

Element& Element::operator=(int val)
{
	SetInt32(val);
	return *this;
}

Element& Element::operator=(__int64 val)
{
	SetInt64(val);
	return *this;
}

Element& Element::operator=(unsigned char val)
{
	SetUChar(val);
	return *this;
}

Element& Element::operator=(unsigned short val)
{
	SetUInt16(val);
	return *this;
}

Element& Element::operator=(unsigned int val)
{
	SetUInt32(val);
	return *this;
}

Element& Element::operator=(unsigned __int64 val)
{
	SetUInt64(val);
	return *this;
}

Element& Element::operator=(float val)
{
	SetFloat(val);
	return *this;
}

Element& Element::operator=(double val)
{
	SetDouble(val);
	return *this;
}

Element& Element::operator=(const std::wstring& val)
{
	SetString(val);
	return *this;
}

Element& Element::operator=(const std::string& val)
{
	SetString(val);
	return *this;
}

Element& Element::operator=(const CString& val)
{
	SetCString(val);
	return *this;
}

Element& Element::operator=(LPCWSTR val)
{
	SetString(std::wstring(val));
	return *this;
}

Element& Element::operator=(LPCSTR val)
{
	SetString(std::string(val));
	return *this;
}

Element& Element::operator=(const GUID& val)
{
	SetGUID(val);
	return *this;
}

Element& Element::operator=(const Elmax::Date& val)
{
	SetDate(val);
	return *this;
}

Element& Element::operator=(const Elmax::DateAndTime& val)
{
	SetDateTime(val);
	return *this;
}

bool Element::SetBool(bool val)
{
	std::wstring strDest;
	if( BaseConverter::SetBool(strDest, val) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Element::SetChar(char val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetInt16(short val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetInt32(int val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetInt64(__int64 val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUChar(unsigned char val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUInt16(unsigned short val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUInt32(unsigned int val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUInt64(unsigned __int64 val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetFloat(float val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetDouble(double val)
{
	std::string temp = boost::lexical_cast<std::string>(val);
	std::wstring strDest = BaseConverter::ConvToString(temp);
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetString(const std::wstring& val)
{
	if(false==m_strNonExistingParent.empty()||false==m_bValid)
	{
		*this = CreateNew();
	}

	if(m_ptrNode)
	{
		m_ptrNode->Puttext(val.c_str());
	}
	else
		return false;

	return true;
}

bool Element::SetString(const std::string& val)
{
	std::wstring strDest;
	if( BaseConverter::SetString(strDest, val) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Element::SetCString(const CString& val)
{
	return SetString((LPCWSTR)(val));
}

bool Element::SetGUID(const GUID& val, bool bRemoveBraces)
{
	std::wstring strDest;
	if( BaseConverter::SetGUID(strDest, val, bRemoveBraces) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Element::SetDate(const Elmax::Date& val)
{
	std::wstring strDest = val.GetString();
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetDateTime(const Elmax::DateAndTime& val)
{
	std::wstring strDest = val.GetString();
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetFileContents(const std::wstring& filepath, bool bSaveFilename, bool bSaveFileLength)
{
	if(FALSE==PathFileExistsW(filepath.c_str()))
		return false;

	FILE* fp = NULL;
	errno_t err = _wfopen_s(&fp, filepath.c_str(), L"rb");
	if(NULL==fp)
		return false;

	struct _stat st;
	_wstat(filepath.c_str(), &st);

	size_t size = st.st_size;

	char* pBuf = new char[size];
	if(NULL==pBuf)
		return false;

	size_t totalRead = fread(pBuf, 1, size, fp);

	if(totalRead!=size)
	{
		delete [] pBuf;
		pBuf = NULL;
		fclose(fp);
		fp = NULL;
		return false;
	}

	std::wstring strDest = ConvToBase64(pBuf, size);

	delete [] pBuf;
	pBuf = NULL;
	fclose(fp);
	fp = NULL;

	if(SetString(strDest))
	{
		if(bSaveFilename)
		{
			std::wstring filename = PathFindFileNameW(filepath.c_str());
			Attr(L"FileName").SetString(filename);
		}
		if(bSaveFileLength)
			Attr(L"FileLength").SetUInt32(size);
		return true;
	}

	return false;
}

bool Element::SetHex(unsigned int val, bool bAddPrefix)
{
	std::wstring strDest;
	if( BaseConverter::SetHex(strDest, val, bAddPrefix) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Element::GetString(const std::wstring& defaultVal, std::wstring& val) const
{
	if(false==m_strNonExistingParent.empty()||false==m_bValid)
		return false;

	if(m_ptrNode)
	{
		bstr_t text = m_ptrNode->Gettext();
		val = (LPCWSTR)(text);
		if(val.empty())
			val = defaultVal;
	}
	else 
		val = defaultVal;
	
	return true;
}

bool Element::GetBool(bool defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	bool val = defaultVal;
	BaseConverter::GetBool(src, defaultVal, val);
	return val;
}

char Element::GetChar(char defaultVal) const
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

short Element::GetInt16(short defaultVal) const
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

int Element::GetInt32(int defaultVal) const
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

__int64 Element::GetInt64(__int64 defaultVal) const
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

unsigned char Element::GetUChar(unsigned char defaultVal) const
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

unsigned short Element::GetUInt16(unsigned short defaultVal) const
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

unsigned int Element::GetUInt32(unsigned int defaultVal) const
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

unsigned __int64 Element::GetUInt64(unsigned __int64 defaultVal) const
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

float Element::GetFloat(float defaultVal) const
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

double Element::GetDouble(double defaultVal) const
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

std::wstring Element::GetString(const std::wstring& defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	std::wstring val = defaultVal;
	BaseConverter::GetString(src, defaultVal, val);
	return val;
}

std::string Element::GetString(const std::string& defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	std::string val = defaultVal;
	BaseConverter::GetString(src, defaultVal, val);
	return val;
}

CString Element::GetCString(const CString& defaultVal) const
{
	return GetString((LPCWSTR)(defaultVal)).c_str();
}

GUID Element::GetGUID(const GUID& defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	GUID val = defaultVal;
	BaseConverter::GetGUID(src, defaultVal, val);
	return val;
}

Elmax::Date Element::GetDate(const Elmax::Date& defaultVal) const
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

Elmax::DateAndTime Element::GetDateTime(const Elmax::DateAndTime& defaultVal) const
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

char* Element::GetFileContents(std::wstring& filename, int& length)
{
	std::wstring src;
	if(false==GetString(L"", src))
	{
		length = 0;
		return NULL;
	}

	length = 0;

	Element::ConvFromBase64(src, NULL, length);

	char* p = new char[length];
	memset(p, 0, length);

	Element::ConvFromBase64(src, p, length);

	filename = Attr(L"FileName").GetString(L"");

	return p;
}

unsigned int Element::ReadHex(unsigned int defaultVal) const
{
	std::wstring src;
	if(false==GetString(L"", src))
		return defaultVal;

	unsigned int val = defaultVal;
	BaseConverter::ReadHex(src, defaultVal, val);
	return val;
}

bool Element::AddCData(const std::wstring& data)
{
	if(!m_ptrNode||false==m_strNonExistingParent.empty()||false==m_bValid)
	{
		throw std::runtime_error("Invalid Element");
	}
	else // if(m_strNonExistingParent.empty())
	{
		if(m_ptrDoc&&m_ptrNode)
		{
			MSXML2::IXMLDOMNodePtr pNew = m_ptrDoc->createNode(MSXML2::NODE_CDATA_SECTION, data.c_str(), L"");
			pNew->nodeValue = bstr_t(data.c_str());
			m_ptrNode->appendChild(pNew);
			return true;
		}
	}

	return false;
}

bool Element::DeleteAllCData()
{
	std::vector<CData> vec = GetCDataCollection();

	if(vec.size()==0)
		return false;

	for(size_t i=0; i<vec.size(); ++i)
		vec.at(i).Delete();

	return true;
}

std::vector<CData> Element::GetCDataCollection()
{
	std::vector<CData> vec;
	if(!m_ptrNode||false==m_strNonExistingParent.empty()||false==m_bValid)
		throw std::runtime_error("Invalid Element");

	MSXML2::IXMLDOMNodeListPtr pList = m_ptrNode->GetchildNodes();
	vec.clear();
	if(pList)
	{
		long len = pList->Getlength();
		bool found = false;
		for(long j=0; j<len; ++j)
		{
			MSXML2::IXMLDOMNodePtr pNode = pList->Getitem(j);
			if(pNode&&pNode->nodeType==MSXML2::NODE_CDATA_SECTION)
			{
				vec.push_back(CData(pNode));
			}
		}
	}

	return vec;
}

bool Element::AddComment(const std::wstring& comment)
{
	if(!m_ptrNode||false==m_strNonExistingParent.empty()||false==m_bValid)
	{
		throw std::runtime_error("Invalid Element");
	}
	else // if(m_strNonExistingParent.empty())
	{
		if(m_ptrDoc&&m_ptrNode)
		{
			MSXML2::IXMLDOMNodePtr pNew = m_ptrDoc->createNode(MSXML2::NODE_COMMENT, comment.c_str(), L"");
			if(pNew)
			{
				pNew->Puttext(comment.c_str());
				m_ptrNode->appendChild(pNew);
				return true;
			}
		}
	}

	return false;
}

bool Element::DeleteAllComments()
{
	std::vector<Comment> vec = GetCommentCollection();

	if(vec.size()==0)
		return false;

	for(size_t i=0; i<vec.size(); ++i)
		vec.at(i).Delete();

	return true;
}

std::vector<Comment> Element::GetCommentCollection()
{
	std::vector<Comment> vec;
	if(!m_ptrNode||false==m_strNonExistingParent.empty()||false==m_bValid)
		throw std::runtime_error("Invalid Element");

	MSXML2::IXMLDOMNodeListPtr pList = m_ptrNode->GetchildNodes();
	vec.clear();
	if(pList)
	{
		long len = pList->Getlength();
		bool found = false;
		for(long j=0; j<len; ++j)
		{
			MSXML2::IXMLDOMNodePtr pNode = pList->Getitem(j);
			if(pNode&&pNode->nodeType==MSXML2::NODE_COMMENT)
			{
				vec.push_back(Comment(pNode));
			}
		}
	}

	return vec;
}

std::wstring Element::ConvToBase64(const char* pSrc, int len)
{
	std::wstring wstrBase64Dest;
	ConvToBase64(pSrc, len, wstrBase64Dest);
	return wstrBase64Dest;
}

bool Element::ConvToBase64(const char* pSrc, int len, std::wstring& wstrBase64Dest)
{
	if(!pSrc||len<=0)
		return false;

	int base64Length = Base64EncodeGetRequiredLength(len);

	char* pB64Output = new char[base64Length+1];
	memset(pB64Output, 0, base64Length+1);
	BOOL bRet = Base64Encode((const BYTE*)(pSrc),
		len,
		pB64Output,
		&base64Length);

	if(bRet==FALSE)
	{
		delete [] pB64Output;
		return false;
	}

	const size_t size = base64Length+1;
	wchar_t* pbuf = new wchar_t[size];

	if( !pbuf )
	{
		delete [] pB64Output;
		return false;
	}

	memset( pbuf, 0, size*sizeof(wchar_t) );

	size_t nConverted=0;
	errno_t nRet = mbstowcs_s(
		&nConverted,
		pbuf,
		size,
		pB64Output,
		_TRUNCATE );

	if( 0 == nRet )
		wstrBase64Dest = pbuf;
	else
		return false;

	delete [] pbuf;
	delete [] pB64Output;

	return true;
}

bool Element::ConvFromBase64(const std::wstring& wstrBase64Src, char* pDest, int& len)
{
	int decodeSize = Base64DecodeGetRequiredLength(wstrBase64Src.size());
	if(NULL==pDest)
	{
		len = decodeSize;
		return true;
	}

	if(wstrBase64Src.empty())
		return false;

	const size_t srcSize = wstrBase64Src.size()+1;
	char* pB64Input = new char[srcSize];
	if( NULL == pB64Input )
		return false;
	memset( pB64Input, 0, srcSize );
	size_t RetSize=0;
	errno_t err = wcstombs_s( &RetSize, pB64Input, srcSize, wstrBase64Src.c_str(), srcSize );

	if( 0 != err )
	{
		delete [] pB64Input;
		return false;
	}


	if (!Base64Decode(pB64Input, srcSize-1, reinterpret_cast<BYTE*>(pDest), &len))
	{
		delete [] pB64Input;
		return false;
	}

	delete [] pB64Input;

	return true;
}

Elmax::Attribute Element::Attr(const std::wstring& attrName)
{
	if(!m_ptrNode || false==m_strNonExistingParent.empty() || false==m_bValid)
		return Elmax::Attribute();

	//if(false==m_strNonExistingParent.empty()||false==m_bValid)
	//{
	//	*this = CreateNew();
	//}

	m_Attribute.SetParam(m_ptrDoc, m_ptrNode, attrName);
	return m_Attribute;
}

Elmax::Attribute Element::Attr(const std::string& attrName)
{
	if(!m_ptrNode || false==m_strNonExistingParent.empty() || false==m_bValid)
		return Elmax::Attribute();

	// convert the ascii string to wide string
	std::wstring wattrName = L"";
	BaseConverter::SetString(wattrName, attrName);

	m_Attribute.SetParam(m_ptrDoc, m_ptrNode, wattrName);
	return m_Attribute;
}

std::vector<std::wstring> Element::GetAttrNames()
{
	std::vector<std::wstring> vec;

	if(!m_ptrNode||false==m_strNonExistingParent.empty()||false==m_bValid)
		return vec;

	if(m_ptrDoc&&m_ptrNode)
	{
		MSXML2::IXMLDOMNamedNodeMapPtr attrList = m_ptrNode->Getattributes();

		if(attrList)
		{
			for(long i=0; i<attrList->length; ++i)
			{
				std::wstring name = (LPCWSTR)(attrList->item[i]->GetnodeName());
				vec.push_back(name);
			}
		}
	}

	return vec;
}

std::vector<Elmax::Attribute> Element::GetAllAttr()
{
	std::vector<Elmax::Attribute> vec;

	if(!m_ptrNode||false==m_strNonExistingParent.empty()||false==m_bValid)
		return vec;

	if(m_ptrDoc&&m_ptrNode)
	{
		MSXML2::IXMLDOMNamedNodeMapPtr attrList = m_ptrNode->Getattributes();

		if(attrList)
		{
			for(long i=0; i<attrList->length; ++i)
			{
				Elmax::Attribute attr;
				attr.SetParam(m_ptrDoc, m_ptrNode, (LPCWSTR)(attrList->item[i]->GetnodeName()));
				vec.push_back(attr);
			}
		}
	}

	return vec;
}

Element Element::SelectSingleNode(const std::wstring& szXPath)
{
	if(m_ptrNode!=NULL&&m_bValid&&m_strNonExistingParent.empty())
	{
		MSXML2::IXMLDOMNodePtr pNode = m_ptrNode->selectSingleNode(_bstr_t(szXPath.c_str()));

		if(pNode)
		{
			return Element(m_ptrDoc, pNode, L"", (LPCWSTR)(pNode->nodeName), true, false);
		}
	}

	return Element();
}

std::vector<Element> Element::SelectNodes(const std::wstring& szXPath)
{
	std::vector<Element> vec;
	if(m_ptrNode!=NULL&&m_bValid&&m_strNonExistingParent.empty())
	{
		MSXML2::IXMLDOMNodeListPtr pList = m_ptrNode->selectNodes(_bstr_t(szXPath.c_str()));

		if(pList)
		{
			for(long i=0; i<pList->length; ++i)
			{
				Element ele(m_ptrDoc, pList->item[i], L"", (LPCWSTR)(pList->item[i]->nodeName), true, false);
				vec.push_back(ele);
			}
		}
	}
	return vec;
}

bool Element::Add(NewNode& node1)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}


bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node7.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node7.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node8.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node7.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node8.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node9.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node7.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node8.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node9.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node10.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node7.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node8.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node9.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node10.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node11.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node7.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node8.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node9.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node10.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node11.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node12.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node7.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node8.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node9.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node10.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node11.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node12.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node13.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node7.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node8.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node9.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node10.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node11.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node12.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node13.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node14.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node7.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node8.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node9.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node10.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node11.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node12.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node13.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node14.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node15.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

bool Element::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15, NewNode& node16)
{
	if(!m_ptrDoc||!m_ptrNode)
		throw std::runtime_error("No valid xml document and node in this element!");

	std::wstring name = m_ptrNode->nodeName;
	std::wstring value = m_ptrNode->Gettext();

	NewElement elem(name, value);
	NewTreeNode* tmpPtr = node1.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node2.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node3.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node4.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node5.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node6.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node7.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node8.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node9.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node10.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node11.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node12.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node13.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node14.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node15.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);
	tmpPtr = node16.GetPtr();
	if(tmpPtr!=NULL)
		elem.Append(tmpPtr);

	bool bRet = NewTreeNode::Traverse(m_ptrDoc, m_ptrNode, elem.GetPtr());

	elem.Discard();

	return bRet;
}

__int64 Element::Min(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	__int64 nMin = 0;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	bool init = false;
	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of minimum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					nMin = list[i].GetInt64(0);
					init = true;
				}
				else
				{
					__int64 val = list[i].GetInt64(0);
					if(val < nMin)
						nMin = val;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						nMin = sub.GetInt64(0);
						init = true;
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{						
						__int64 val = sub.GetInt64(0);
						if(val < nMin)
							nMin = val;
					}
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of minimum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						nMin = attr1.GetInt64(0);
						init = true;
					}
				}
				else
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						__int64 val = attr1.GetInt64(0);
						if(val < nMin)
							nMin = val;
					}
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							nMin = attr1.GetInt64(0);
							init = true;
						}
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							__int64 val = attr1.GetInt64(0);
							if(val < nMin)
								nMin = val;
						}
					}
				}
			}
		}
	}

	return nMin;
}

__int64 Element::Max(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	__int64 nMax = 0;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	bool init = false;
	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of maximum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					nMax = list[i].GetInt64(0);
					init = true;
				}
				else
				{
					__int64 val = list[i].GetInt64(0);
					if(val > nMax)
						nMax = val;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						nMax = sub.GetInt64(0);
						init = true;
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{						
						__int64 val = sub.GetInt64(0);
						if(val > nMax)
							nMax = val;
					}
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of maximum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						nMax = attr1.GetInt64(0);
						init = true;
					}
				}
				else
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						__int64 val = attr1.GetInt64(0);
						if(val > nMax)
							nMax = val;
					}
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							nMax = attr1.GetInt64(0);
							init = true;
						}
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							__int64 val = attr1.GetInt64(0);
							if(val > nMax)
								nMax = val;
						}
					}
				}
			}
		}
	}

	return nMax;
}

__int64 Element::Sum(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	__int64 nSum = 0;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for sum computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				__int64 val = list[i].GetInt64(0);
				nSum += val;
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{						
					__int64 val = sub.GetInt64(0);
					nSum += val;
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for sum computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Attribute attr1 = list[i].Attr(attr);
				if(attr1.Exists())
				{
					__int64 val = attr1.GetInt64(0);
					nSum += val;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{
					Elmax::Attribute attr1 = sub.Attr(attr);
					if(attr1.Exists())
					{
						__int64 val = attr1.GetInt64(0);
						nSum += val;
					}
				}
			}
		}
	}

	return nSum;

}

__int64 Element::Avg(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	__int64 nSum = 0;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	int validCnt = 0;
	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for average computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				__int64 val = list[i].GetInt64(0);
				nSum += val;
				++validCnt;
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{						
					__int64 val = sub.GetInt64(0);
					nSum += val;
					++validCnt;
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for average computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Attribute attr1 = list[i].Attr(attr);
				if(attr1.Exists())
				{
					__int64 val = attr1.GetInt64(0);
					nSum += val;
					++validCnt;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{
					Elmax::Attribute attr1 = sub.Attr(attr);
					if(attr1.Exists())
					{
						__int64 val = attr1.GetInt64(0);
						nSum += val;
						++validCnt;

					}
				}
			}
		}
	}

	if(validCnt<=0)
	{
		throw std::runtime_error("No valid element found for average computation!");
	}
	return nSum / validCnt;
}

float Element::MinF(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	float fMin = 0.0f;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	bool init = false;
	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of minimum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					fMin = list[i].GetFloat(0.0f);
					init = true;
				}
				else
				{
					float val = list[i].GetFloat(0.0f);
					if(val < fMin)
						fMin = val;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						fMin = sub.GetFloat(0.0f);
						init = true;
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{						
						float val = sub.GetFloat(0.0f);
						if(val < fMin)
							fMin = val;
					}
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of minimum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						fMin = attr1.GetFloat(0.0f);
						init = true;
					}
				}
				else
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						float val = attr1.GetFloat(0.0f);
						if(val < fMin)
							fMin = val;
					}
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							fMin = attr1.GetFloat(0.0f);
							init = true;
						}
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							float val = attr1.GetFloat(0.0f);
							if(val < fMin)
								fMin = val;
						}
					}
				}
			}
		}
	}

	return fMin;

}

float Element::MaxF(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	float fMax = 0.0f;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	bool init = false;
	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of maximum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					fMax = list[i].GetFloat(0.0f);
					init = true;
				}
				else
				{
					float val = list[i].GetFloat(0.0f);
					if(val > fMax)
						fMax = val;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						fMax = sub.GetFloat(0.0f);
						init = true;
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{						
						float val = sub.GetFloat(0.0f);
						if(val > fMax)
							fMax = val;
					}
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of maximum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						fMax = attr1.GetFloat(0.0f);
						init = true;
					}
				}
				else
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						float val = attr1.GetFloat(0.0f);
						if(val > fMax)
							fMax = val;
					}
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							fMax = attr1.GetFloat(0.0f);
							init = true;
						}
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							float val = attr1.GetFloat(0.0f);
							if(val > fMax)
								fMax = val;
						}
					}
				}
			}
		}
	}

	return fMax;
}

float Element::SumF(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	float fSum = 0.0f;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for sum computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				float val = list[i].GetFloat(0.0f);
				fSum += val;
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{						
					float val = sub.GetFloat(0.0f);
					fSum += val;
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for sum computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Attribute attr1 = list[i].Attr(attr);
				if(attr1.Exists())
				{
					float val = attr1.GetFloat(0.0f);
					fSum += val;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{
					Elmax::Attribute attr1 = sub.Attr(attr);
					if(attr1.Exists())
					{
						float val = attr1.GetFloat(0.0f);
						fSum += val;
					}
				}
			}
		}
	}

	return fSum;
}

float Element::AvgF(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	float fSum = 0.0f;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	int validCnt = 0;
	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for average computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				float val = list[i].GetFloat(0.0f);
				fSum += val;
				++validCnt;
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{						
					float val = sub.GetFloat(0.0f);
					fSum += val;
					++validCnt;
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for average computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Attribute attr1 = list[i].Attr(attr);
				if(attr1.Exists())
				{
					float val = attr1.GetFloat(0.0f);
					fSum += val;
					++validCnt;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{
					Elmax::Attribute attr1 = sub.Attr(attr);
					if(attr1.Exists())
					{
						float val = attr1.GetFloat(0.0f);
						fSum += val;
						++validCnt;
					}
				}
			}
		}
	}

	if(validCnt<=0)
	{
		throw std::runtime_error("No valid element found for average computation!");
	}
	return fSum / validCnt;
}

double Element::MinD(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	double dMin = 0.0;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	bool init = false;
	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of minimum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					dMin = list[i].GetDouble(0.0);
					init = true;
				}
				else
				{
					double val = list[i].GetDouble(0.0);
					if(val < dMin)
						dMin = val;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						dMin = sub.GetDouble(0.0);
						init = true;
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{						
						double val = sub.GetDouble(0.0);
						if(val < dMin)
							dMin = val;
					}
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of minimum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						dMin = attr1.GetDouble(0.0);
						init = true;
					}
				}
				else
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						double val = attr1.GetDouble(0.0);
						if(val < dMin)
							dMin = val;
					}
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							dMin = attr1.GetDouble(0.0);
							init = true;
						}
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							double val = attr1.GetDouble(0.0);
							if(val < dMin)
								dMin = val;
						}
					}
				}
			}
		}
	}

	return dMin;

}

double Element::MaxD(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	double dMax = 0.0;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	bool init = false;
	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of maximum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					dMax = list[i].GetDouble(0.0);
					init = true;
				}
				else
				{
					double val = list[i].GetDouble(0.0);
					if(val > dMax)
						dMax = val;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						dMax = sub.GetDouble(0.0);
						init = true;
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{						
						double val = sub.GetDouble(0.0);
						if(val > dMax)
							dMax = val;
					}
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for computation of maximum value!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						dMax = attr1.GetDouble(0.0);
						init = true;
					}
				}
				else
				{
					Elmax::Attribute attr1 = list[i].Attr(attr);
					if(attr1.Exists())
					{
						double val = attr1.GetDouble(0.0);
						if(val > dMax)
							dMax = val;
					}
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				if(init == false)
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							dMax = attr1.GetDouble(0.0);
							init = true;
						}
					}
				}
				else
				{
					Elmax::Element sub = list[i][subElemName.c_str()];
					if(sub.Exists())
					{
						Elmax::Attribute attr1 = sub.Attr(attr);
						if(attr1.Exists())
						{
							double val = attr1.GetDouble(0.0);
							if(val > dMax)
								dMax = val;
						}
					}
				}
			}
		}
	}

	return dMax;
}

double Element::SumD(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	double dSum = 0.0;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for sum computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				double val = list[i].GetDouble(0.0);
				dSum += val;
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{						
					double val = sub.GetDouble(0.0);
					dSum += val;
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for sum computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Attribute attr1 = list[i].Attr(attr);
				if(attr1.Exists())
				{
					double val = attr1.GetDouble(0.0);
					dSum += val;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{
					Elmax::Attribute attr1 = sub.Attr(attr);
					if(attr1.Exists())
					{
						double val = attr1.GetDouble(0.0);
						dSum += val;
					}
				}
			}
		}
	}

	return dSum;
}

double Element::AvgD(const std::wstring& elem, const std::wstring& attr)
{
	std::wstring collectionName = L"";
	std::wstring subElemName = L"";
	double nSum = 0.0;
	if(elem.find(L'|')!=-1||elem.find(L'\\')!=-1||elem.find(L'/')!=-1)
	{
		if(elem.length()>0)
		{
			size_t i=0;
			while(elem[i]!=L'|'&&elem[i]!=L'\\'&&elem[i]!=L'/'&&i<elem.length())
			{
				collectionName += elem[i];
				++i;
			}
			subElemName = elem.substr(i+1, elem.length()-(i+1));
		}
	}
	else
		collectionName = elem;

	int validCnt = 0;
	if(attr == L"")
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for average computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				double val = list[i].GetDouble(0.0);
				nSum += val;
				++validCnt;
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{						
					double val = sub.GetDouble(0.0);
					nSum += val;
					++validCnt;
				}
			}
		}
	}
	else // attribute is specified
	{
		collection_t list = this->GetChildren(collectionName);
		if(list.size()<=0)
		{
			throw std::runtime_error("No element found for average computation!");
		}
		if(subElemName == L"")
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Attribute attr1 = list[i].Attr(attr);
				if(attr1.Exists())
				{
					double val = attr1.GetDouble(0.0);
					nSum += val;
					++validCnt;
				}
			}
		}
		else // there is sub element specified
		{
			for(size_t i=0; i<list.size(); ++i)
			{
				Elmax::Element sub = list[i][subElemName.c_str()];
				if(sub.Exists())
				{
					Elmax::Attribute attr1 = sub.Attr(attr);
					if(attr1.Exists())
					{
						double val = attr1.GetDouble(0.0);
						nSum += val;
						++validCnt;

					}
				}
			}
		}
	}

	if(validCnt<=0)
	{
		throw std::runtime_error("No valid element found for average computation!");
	}
	return nSum / validCnt;
}
