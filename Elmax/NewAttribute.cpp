#include "StdAfx.h"
#include "NewAttribute.h"

using namespace Elmax;

NewAttribute::NewAttribute(const std::wstring& name, const std::wstring& sValue)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_ATTRIBUTE;
		ptr->pName = name;
		ptr->pValue = sValue;
	}

}


NewAttribute::~NewAttribute(void)
{
}
