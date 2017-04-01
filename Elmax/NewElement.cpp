#include "StdAfx.h"
#include "NewElement.h"
#include "Document.h"
#include <vector>

using namespace Elmax;

NewElement::NewElement()
{
}

NewElement::NewElement(const std::wstring& name)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;
	}
}

NewElement::NewElement(const std::wstring& name, const std::wstring& sValue)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;
		ptr->pValue = sValue;
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}
NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}


NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node12.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node12.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node13.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node12.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node13.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node14.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node12.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node13.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node14.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node15.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::NewElement(const std::wstring& name, NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15, NewNode& node16)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ELEMENT;
		ptr->pName = name;

		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node12.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node13.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node14.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node15.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node16.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
}

NewElement::~NewElement(void)
{
}

bool NewElement::Append(NewTreeNode* child)
{
	if(!child)
		return false;

	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->vec.push_back(child);
	}
	return true;
}

NewElement NewElement::Add(NewNode& node1)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}


NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node12.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node12.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node13.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node12.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node13.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node14.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node12.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node13.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node14.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node15.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::Add(NewNode& node1, NewNode& node2, NewNode& node3, NewNode& node4, NewNode& node5, 
	NewNode& node6, NewNode& node7, NewNode& node8, NewNode& node9, NewNode& node10,
	NewNode& node11, NewNode& node12, NewNode& node13, NewNode& node14, NewNode& node15, NewNode& node16)
{
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		NewTreeNode* tmpPtr = node1.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node2.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node3.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node4.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node5.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node6.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node7.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node8.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node9.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node10.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node11.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node12.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node13.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node14.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node15.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
		tmpPtr = node16.GetPtr();
		if(tmpPtr!=NULL)
			Append(tmpPtr);
	}
	return *this;
}

NewElement NewElement::operator[](LPCWSTR name)
{
	return Find(name);
}

NewElement NewElement::operator[](LPCSTR name)
{
	BaseConverter* conv = new BaseConverter();

	// convert the ascii string to wide string
	std::wstring wname = L"";
	conv->SetString(wname, name);

	delete conv;

	return Find(wname);
}

NewElement NewElement::Find(const std::wstring& names)
{
	std::vector<std::wstring> vec;
	bool bMultipleParent = false;

	using namespace std;
	std::wstring temp = names;
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

	NewElement elem = *this;

	for(size_t i=0; i<vec.size(); ++i)
	{
		elem = elem.FindFirstChild(vec[i]);

		if(elem.Exists()==false)
			return NewElement();
	}

	return elem;
}

NewElement NewElement::FindFirstChild(const std::wstring& name)
{
	NewTreeNode* ptr = GetPtr();

	if(ptr)
	{
		for(size_t i=0;i<ptr->vec.size();++i)
		{
			if(ptr->vec[i]->pName==name)
			{
				NewElement elem;
				elem.SetPtr(ptr->vec[i]);
				return elem;
			}
		}
	}
	return NewElement();
}

//! Copy constructor
NewElement::NewElement(const NewElement& other)
{
	this->SetPtr(other.GetPtr());
}

//! Assignment operator
NewElement& NewElement::operator=(const NewElement& other)
{
	this->SetPtr(other.GetPtr());
	return *this;
}

bool NewElement::Save(const std::wstring& file, const std::wstring& xmlVersion, bool utf8, bool discard)
{
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

	NewTreeNode* node = this->GetPtr();

	Traverse(*node, uf, utf8);

	uf.Flush();
	uf.Close();

	if(discard)
		this->Discard();

	return true;
}

bool NewElement::Save(const std::wstring& file, ProcessingInstruction& procInstruction, bool discard)
{
	bool utf8 = procInstruction.utf8;

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
	if(procInstruction.noProcessingInstruction==false)
	{
		procInst = procInstruction.ToString();
		Write(uf, utf8, procInst);
	}

	NewTreeNode* node = this->GetPtr();

	Traverse(*node, uf, utf8);

	uf.Flush();
	uf.Close();

	if(discard)
		this->Discard();

	return true;
}

bool NewElement::PrettySave(const std::wstring& file, const std::wstring& xmlVersion, bool utf8, const std::wstring& indent, bool discard)
{
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

	NewTreeNode* node = this->GetPtr();

	Traverse(*node, uf, utf8, 0, indent);

	uf.Flush();
	uf.Close();

	if(discard)
		this->Discard();

	return true;
}

bool NewElement::PrettySave(const std::wstring& file, ProcessingInstruction& procInstruction, const std::wstring& indent, bool discard)
{
	bool utf8 = procInstruction.utf8;

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
	if(procInstruction.noProcessingInstruction==false)
	{
		procInst = procInstruction.ToString();
		Write(uf, utf8, procInst);
	}

	NewTreeNode* node = this->GetPtr();

	if(procInstruction.noProcessingInstruction)
	{
		TraverseWithoutProcessingInstruction(*node, uf, utf8, 0, indent);
	}
	else
	{
		Traverse(*node, uf, utf8, 0, indent);
	}

	uf.Flush();
	uf.Close();

	if(discard)
		this->Discard();

	return true;
}

bool NewElement::Write(CUnicodeFile& uf, bool utf8, const std::wstring& str)
{
	if(utf8)
		uf.WriteUtf8(str);
	else
		uf.Write(str);

	return true;
}

bool NewElement::WriteNewLine(CUnicodeFile& uf, bool utf8)
{
	if(utf8)
		uf.WriteUtf8(L"\n");
	else
		uf.Write(L"\n");

	return true;
}

bool NewElement::WriteIndent(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent)
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

bool NewElement::WriteStartElement(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& elementName, const std::wstring& indent)
{
	WriteNewLine(uf, utf8);
	WriteIndent(uf, utf8, cnt, indent);
	std::wstring str = L"<";
	Write(uf, utf8, str+elementName);
	return true;
}

bool NewElement::WriteFirstStartElement(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& elementName, const std::wstring& indent)
{
	WriteIndent(uf, utf8, cnt, indent);
	std::wstring str = L"<";
	Write(uf, utf8, str+elementName);
	return true;
}

bool NewElement::WriteEndElement(CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& elementName, const std::wstring& indent)
{
	WriteIndent(uf, utf8, cnt, indent);
	std::wstring str = L"</";
	Write(uf, utf8, str+elementName+L">");
	return true;
}

bool NewElement::Traverse(NewTreeNode& node, CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent)
{
	if(node.xmltype==XML_ELEMENT)
	{
		WriteStartElement(uf, utf8, cnt, node.pName, indent);

		bool textValueWritten = false;
		bool attrOnly = false;
		bool attrWritten = false;
		
		++cnt;
		for(size_t i=0;i<node.vec.size(); ++i)
		{
			NewTreeNode* node1 = node.vec[i];
			if(node1->xmltype==XML_ATTRIBUTE)
			{
				attrOnly = true;
				std::wstring str = L" ";
				str += node1->pName + L"=\"";
				str += EscapeXML(node1->pValue);
				str += L"\"";
				Write(uf, utf8, str);

				continue;
			}
			else
			{
				attrOnly = false;
				if(attrWritten == false)
				{
					Write(uf, utf8, L">");
					attrWritten = true;
				}
			}
			Traverse(*node1, uf, utf8, cnt, indent);
		}
		--cnt;

		if (true == attrOnly && false == attrWritten)
		{
			Write(uf, utf8, L"/>");
			attrWritten = true;
		}

		if(node.vec.size()==0)
			Write(uf, utf8, L">");

		if(node.pValue.empty()==false)
		{
			std::wstring str = EscapeXML(node.pValue);
			Write(uf, utf8, str);
			textValueWritten = true;
		}

		if(textValueWritten)
		{
			WriteEndElement(uf, utf8, node.pName);
		}
		else if (false == attrOnly)
		{
			WriteNewLine(uf, utf8);
			WriteEndElement(uf, utf8, cnt, node.pName, indent);
		}
	}
	else if(node.xmltype==XML_COMMENT)
	{
		WriteNewLine(uf, utf8);
		WriteIndent(uf, utf8, cnt, indent);
		std::wstring str = L"<!--";
		str += node.pValue;
		str += L"-->";
		Write(uf, utf8, str);
	}
	else if(node.xmltype==XML_CDATA)
	{
		WriteNewLine(uf, utf8);
		WriteIndent(uf, utf8, cnt, indent);
		std::wstring str = L"<![CDATA[";
		str += node.pValue;
		str += L"]]>";
		Write(uf, utf8, str);
	}

	return true;
}

bool NewElement::TraverseWithoutProcessingInstruction(NewTreeNode& node, CUnicodeFile& uf, bool utf8, size_t cnt, const std::wstring& indent)
{
	if(node.xmltype==XML_ELEMENT)
	{
		WriteFirstStartElement(uf, utf8, cnt, node.pName, indent);

		bool textValueWritten = false;
		++cnt;
		bool attrWritten = false;
		for(size_t i=0;i<node.vec.size(); ++i)
		{
			NewTreeNode* node1 = node.vec[i];
			if(node1->xmltype==XML_ATTRIBUTE)
			{
				std::wstring str = L" ";
				str += node1->pName + L"=\"";
				str += EscapeXML(node1->pValue);
				str += L"\"";
				Write(uf, utf8, str);

				continue;
			}
			else
			{
				if(attrWritten == false)
				{
					Write(uf, utf8, L">");
					attrWritten = true;
				}
			}
			Traverse(*node1, uf, utf8, cnt, indent);
		}
		--cnt;

		if(node.vec.size()==0)
			Write(uf, utf8, L">");

		if(node.pValue.empty()==false)
		{
			std::wstring str = EscapeXML(node.pValue);
			Write(uf, utf8, str);
			textValueWritten = true;
		}

		if(textValueWritten)
		{
			WriteEndElement(uf, utf8, node.pName);
		}
		else
		{
			WriteNewLine(uf, utf8);
			WriteEndElement(uf, utf8, cnt, node.pName, indent);
		}
	}
	else if(node.xmltype==XML_COMMENT)
	{
		WriteNewLine(uf, utf8);
		WriteIndent(uf, utf8, cnt, indent);
		std::wstring str = L"<!--";
		str += node.pValue;
		str += L"-->";
		Write(uf, utf8, str);
	}
	else if(node.xmltype==XML_CDATA)
	{
		WriteNewLine(uf, utf8);
		WriteIndent(uf, utf8, cnt, indent);
		std::wstring str = L"<![CDATA[";
		str += node.pValue;
		str += L"]]>";
		Write(uf, utf8, str);
	}

	return true;
}

bool NewElement::WriteStartElement(CUnicodeFile& uf, bool utf8, const std::wstring& elementName)
{
	std::wstring str = L"<";
	Write(uf, utf8, str+elementName);
	return true;
}

bool NewElement::WriteEndElement(CUnicodeFile& uf, bool utf8, const std::wstring& elementName)
{
	std::wstring str = L"</";
	Write(uf, utf8, str+elementName+L">");
	return true;
}

bool NewElement::Traverse(NewTreeNode& node, CUnicodeFile& uf, bool utf8)
{
	if(node.xmltype==XML_ELEMENT)
	{
		WriteStartElement(uf, utf8, node.pName);

		bool attrWritten = false;
		bool attrOnly = false;

		for(size_t i=0;i<node.vec.size(); ++i)
		{
			NewTreeNode* node1 = node.vec[i];
			if(node1->xmltype==XML_ATTRIBUTE)
			{
				attrOnly = true;
				std::wstring str = L" ";
				str += node1->pName + L"=\"";
				str += EscapeXML(node1->pValue);
				str += L"\"";
				Write(uf, utf8, str);

				continue;
			}
			else
			{
				attrOnly = false;
				if(attrWritten == false)
				{
					Write(uf, utf8, L">");
					attrWritten = true;
				}
			}
			Traverse(*node1, uf, utf8);
		}

		if (true == attrOnly && false == attrWritten)
		{
			Write(uf, utf8, L"/>");
			attrWritten = true;
		}

		if(node.vec.size()==0)
			Write(uf, utf8, L">");

		if(node.pValue.empty()==false)
		{
			std::wstring str = EscapeXML(node.pValue);
			Write(uf, utf8, str);
		}

		if (false == attrOnly)
		{
			WriteEndElement(uf, utf8, node.pName);
		}
	}
	else if(node.xmltype==XML_COMMENT)
	{
		std::wstring str = L"<!--";
		str += node.pValue;
		str += L"-->";
		Write(uf, utf8, str);
	}
	else if(node.xmltype==XML_CDATA)
	{
		std::wstring str = L"<![CDATA[";
		str += node.pValue;
		str += L"]]>";
		Write(uf, utf8, str);
	}

	return true;
}

std::wstring NewElement::Replace( 
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

std::wstring NewElement::EscapeXML( 
	const std::wstring& fmtstr)
{
	std::wstring fmtstr1 = Replace(fmtstr, L"&", L"&amp;");
	fmtstr1 = Replace(fmtstr1, L"\"", L"&quot;");
	fmtstr1 = Replace(fmtstr1, L"\'", L"&apos;");
	fmtstr1 = Replace(fmtstr1, L"<", L"&lt;");
	fmtstr1 = Replace(fmtstr1, L">", L"&gt;");

	return fmtstr1;
}

std::wstring NewElement::UnescapeXML( 
	const std::wstring& fmtstr)
{
	std::wstring fmtstr1 = Replace(fmtstr, L"&amp;", L"&");
	fmtstr1 = Replace(fmtstr1, L"&quot;", L"\"");
	fmtstr1 = Replace(fmtstr1, L"&apos;", L"\'");
	fmtstr1 = Replace(fmtstr1, L"&lt;", L"<");
	fmtstr1 = Replace(fmtstr1, L"&gt;", L">");

	return fmtstr1;
}
