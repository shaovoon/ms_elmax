#pragma once
#include "NewTreeNode.h"

namespace Elmax
{

class NewNode
{
public:
	NewNode(void);
	~NewNode(void);

	NewTreeNode* GetPtr() const {return ptr;}
	void SetPtr(NewTreeNode* src) { ptr = src; }

	void Init();

	void Discard();
private:
	NewTreeNode* ptr;
};


} // ns Elmax
