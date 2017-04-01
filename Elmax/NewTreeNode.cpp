#include "StdAfx.h"
#include "NewTreeNode.h"

using namespace Elmax;

NewTreeNode::NewTreeNode(void)
{
	pName = L"";
	pValue = L"";

	xmltype = XML_NONE;
}


NewTreeNode::~NewTreeNode(void)
{
}

void NewTreeNode::Delete()
{
	for(size_t i=0;i<vec.size();++i)
		vec.at(i)->Delete();

	vec.clear();
	delete this;
}

bool NewTreeNode::Traverse(MSXML2::IXMLDOMDocumentPtr& ptrDoc,  MSXML2::IXMLDOMNodePtr& parent, NewTreeNode* pNode)
{
	if(!ptrDoc||!parent)
		return false;

	if(pNode==NULL)
		return false;

	for(size_t i=0;i<pNode->vec.size();++i)
	{
		NewTreeNode* pNode1 = pNode->vec.at(i);

		if(pNode1->xmltype==XML_ELEMENT)
		{
			_bstr_t str(pNode1->pName.c_str());
			_variant_t varType(MSXML2::NODE_ELEMENT);
			_bstr_t emptyUri(L"");
			MSXML2::IXMLDOMNodePtr elem = ptrDoc->createNode(varType, str, emptyUri);
			parent->appendChild(elem);
			if(pNode1->pValue!=L"")
				elem->Puttext(_bstr_t(pNode1->pValue.c_str()));

			bool b = Traverse(ptrDoc, elem, pNode1);
			if(b==false)
				return false;
		}
		else if(pNode1->xmltype==XML_COMMENT)
		{
			MSXML2::IXMLDOMNodePtr domComment = ptrDoc->createNode(MSXML2::NODE_COMMENT, _bstr_t(pNode1->pName.c_str()), L"");

			if(!domComment)
				return false;

			domComment->Puttext(pNode1->pValue.c_str());

			parent->appendChild(domComment);
		}
		else if(pNode1->xmltype==XML_CDATA)
		{
			MSXML2::IXMLDOMNodePtr domCData = ptrDoc->createNode(MSXML2::NODE_CDATA_SECTION, _bstr_t(pNode1->pValue.c_str()), L"");

			if(!domCData)
				return false;

			domCData->nodeValue = bstr_t(pNode1->pValue.c_str());

			parent->appendChild(domCData);
		}
		else if(pNode1->xmltype==XML_ATTRIBUTE)
		{
			MSXML2::IXMLDOMNamedNodeMapPtr attrList = parent->Getattributes();

			if(!attrList)
				return false;

			MSXML2::IXMLDOMAttributePtr pAttr = ptrDoc->createAttribute(_bstr_t(pNode1->pName.c_str()));

			if(attrList&&pAttr)
			{
				pAttr->Puttext(_bstr_t(pNode1->pValue.c_str()));
				attrList->setNamedItem(pAttr);
			}
		}
	}
	return true;
}