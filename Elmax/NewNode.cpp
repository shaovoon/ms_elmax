#include "StdAfx.h"
#include "NewNode.h"

using namespace Elmax;

NewNode::NewNode(void)
{
	ptr = NULL;
}


NewNode::~NewNode(void)
{
}

void NewNode::Discard()
{
	if(ptr!=NULL)
		ptr->Delete();

	ptr=NULL;
}

void NewNode::Init() 
{
	ptr = new NewTreeNode();
}
