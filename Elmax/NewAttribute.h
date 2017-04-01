#pragma once
#include "NewNode.h"

namespace Elmax
{

class NewAttribute : public NewNode
{
public:
	// Constructors
	NewAttribute(const std::wstring& name, const std::wstring& sValue);
	~NewAttribute(void);
};

} // ns Elmax

