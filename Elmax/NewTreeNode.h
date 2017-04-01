#pragma once
#include <vector>

namespace Elmax
{

enum XMLTYPE
{
	XML_NONE,
	XML_ELEMENT,
	XML_ATTRIBUTE,
	XML_COMMENT,
	XML_CDATA
};

class NewTreeNode
{
public:
	NewTreeNode(void);
	~NewTreeNode(void);

	std::vector<NewTreeNode*> vec;

	std::wstring pName;
	std::wstring pValue;

	XMLTYPE xmltype;

	static bool Traverse(MSXML2::IXMLDOMDocumentPtr& ptrDoc, MSXML2::IXMLDOMNodePtr& parent, NewTreeNode* pNode);
	void Delete();
};

} // ns Elmax

