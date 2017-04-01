#pragma once
#include "AbstractTextout.h"

class DebugPrint :
	public AbstractTextout
{
public:
	DebugPrint(void);
	virtual ~DebugPrint(void);
protected:
	void Process(const std::wstring& str);

};
