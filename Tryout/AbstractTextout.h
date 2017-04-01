/*
TextOut Library for Native C++ version 1.1.2

Copyright (c) 2007 - 2008 Wong Shao Voon

The Code Project Open License (CPOL)
http://www.codeproject.com/info/cpol10.aspx
*/

#pragma once

#pragma warning( disable : 4786 )

#include <vector>
#include "Box.h"

class AbstractTextout
{
public:
	void Print( 
		const wchar_t* fmt);

	void Print( 
		const wchar_t* fmt, 
		Box D1 );

	void Print( 
		const wchar_t* fmt, 
		Box D1, Box D2 );

	void Print( 
		const wchar_t* fmt, 
		Box D1, Box D2, Box D3 );

	void Print( 
		const wchar_t* fmt, 
		Box D1, Box D2, Box D3, Box D4 );

	void Print( 
		const wchar_t* fmt, 
		Box D1, Box D2, Box D3, Box D4, Box D5 );
	
	void Print( 
		const wchar_t* fmt, 
		Box D1, Box D2, Box D3, Box D4, Box D5, Box D6 );
	
	void Print( 
		const wchar_t* fmt, 
		Box D1, Box D2, Box D3, Box D4, Box D5, Box D6, Box D7 );

	void Print( 
		const wchar_t* fmt, 
		Box D1, Box D2, Box D3, Box D4, 
		Box D5, Box D6, Box D7, Box D8 );

	void Print( 
		const wchar_t* fmt, 
		Box D1, Box D2, Box D3, Box D4, 
		Box D5, Box D6, Box D7, Box D8, Box D9 );

	void Print( 
		const wchar_t* fmt, 
		Box D1, Box D2, Box D3, Box D4, Box D5, 
		Box D6, Box D7, Box D8, Box D9, Box D10 );

	std::wstring StrReplace( 
		std::wstring& fmtstr, 
		const std::vector<std::wstring>& vs );

	std::wstring StrAnchor( size_t i );

protected:
	virtual void Process(const std::wstring& str) = 0;


};
