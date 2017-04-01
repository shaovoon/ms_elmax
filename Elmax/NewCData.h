#pragma once
#include "NewNode.h"

namespace Elmax
{

class NewCData : public NewNode
{
public:
	// Constructors
	NewCData(const std::wstring& sValue);

	~NewCData(void);
};

} // ns Elmax

