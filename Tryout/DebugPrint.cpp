#include "StdAfx.h"
#include "DebugPrint.h"
#include <iostream>

DebugPrint::DebugPrint(void)
{
}

DebugPrint::~DebugPrint(void)
{
}

void DebugPrint::Process(const std::wstring& str)
{
#ifdef _DEBUG
	OutputDebugStringW( str.c_str() );
#endif
}
