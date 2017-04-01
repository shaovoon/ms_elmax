/*
TextOut Library for Native C++ version 1.1.2

Copyright (c) 2007 - 2008 Wong Shao Voon

The Code Project Open License (CPOL)
http://www.codeproject.com/info/cpol10.aspx
*/


#pragma once

#include <string>

class Box
{
public:
	Box( int i );

	Box( unsigned int ui );
	
	Box( const __int64& i64 );

	Box( const unsigned __int64& ui64 );

	Box( float f );

	Box( const double& d );

	Box( const std::string& s );
	
	Box( const std::wstring& ws );
	
	Box( const char* pc );

	Box( const wchar_t* pwc );
	
	Box( char c );

	Box( wchar_t wc );

	std::wstring& ToString() { return m_str; }

protected:
	std::wstring m_str;

};
