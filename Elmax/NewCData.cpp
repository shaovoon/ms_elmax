#include "StdAfx.h"
#include "NewCData.h"

using namespace Elmax;

NewCData::NewCData(const std::wstring& sValue)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_CDATA;
		ptr->pValue = sValue;
	}
}


NewCData::~NewCData(void)
{
}
