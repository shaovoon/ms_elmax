#include "StdAfx.h"
#include "NewComment.h"

using namespace Elmax;

NewComment::NewComment(const std::wstring& sValue)
{
	Init();
	NewTreeNode* ptr = GetPtr();
	if(ptr)
	{
		ptr->xmltype = XML_COMMENT;
		ptr->pValue = sValue;
	}
}


NewComment::~NewComment(void)
{
}
