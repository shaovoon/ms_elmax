#pragma once
#include "NewNode.h"

namespace Elmax
{

class NewComment : public NewNode
{
public:
	// Constructors
	NewComment(const std::wstring& sValue);
	~NewComment(void);
};


} // ns Elmax
