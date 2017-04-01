/*
TextOut Library for Native C++ version 1.1.2

Copyright (c) 2007 - 2008 Wong Shao Voon

The Code Project Open License (CPOL)
http://www.codeproject.com/info/cpol10.aspx
*/

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include "Box.h"

Box::Box( int i )
{
	const int size = 20;
	wchar_t buf[size];
	memset( buf, 0, sizeof(buf) );
	errno_t nRet = _itow_s( i, buf, size, 10 );

	if( 0 == nRet )
		m_str = buf;
}
	
Box::Box( unsigned int ui )
{
	const int size = 20;
	wchar_t buf[size];
	memset( buf, 0, sizeof(buf) );
	errno_t nRet = _ultow_s( ui, buf, size, 10 );

	if( 0 == nRet )
		m_str = buf;
}

Box::Box( const __int64& i64 )
{
	const int size = 40;
	wchar_t buf[size];
	memset( buf, 0, sizeof(buf) );
	errno_t nRet = _i64tow_s( i64, buf, size, 10 );

	if( 0 == nRet )
		m_str = buf;
}
	
Box::Box( const unsigned __int64& ui64 )
{
	const int size = 40;
	wchar_t buf[size];
	memset( buf, 0, sizeof(buf) );
	errno_t nRet = _ui64tow_s( ui64, buf, size, 10 );

	if( 0 == nRet )
		m_str = buf;
}

Box::Box( float f )
{
	const int size = 30;
	wchar_t buf[size];
	memset( buf, 0, sizeof(buf) );
	int nRet = swprintf_s( buf, size, L"%f", f );

	if( -1 != nRet )
		m_str = buf;
}

Box::Box( const double& d )
{
	const int size = 30;
	wchar_t buf[size];
	memset( buf, 0, sizeof(buf) );
	int nRet = swprintf_s( buf, size, L"%f", d );

	if( -1 != nRet )
		m_str = buf;
}

Box::Box( const std::string& s )
{
	const size_t size = s.size()+1;
	wchar_t* pbuf = new wchar_t[size];

	if( !pbuf )
		return;

	memset( pbuf, 0, size*sizeof(wchar_t) );

	size_t nConverted=0;
	errno_t nRet = mbstowcs_s(
		&nConverted,
		pbuf,
		size,
		s.c_str(),
		_TRUNCATE );


	if( 0 == nRet )
		m_str = pbuf;

	delete [] pbuf;
}

Box::Box( const std::wstring& ws )
{
	m_str = ws;
}

Box::Box( const char* pc )
{
	const size_t size = strlen(pc)+1;
	wchar_t* pbuf = new wchar_t[size];

	if( !pbuf )
		return;

	memset( pbuf, 0, size*sizeof(wchar_t) );
	size_t nConverted=0;
	errno_t nRet = mbstowcs_s(
		&nConverted,
		pbuf,
		size,
		pc,
		_TRUNCATE );

	if( 0 == nRet )
		m_str = pbuf;

	delete [] pbuf;
}

Box::Box( const wchar_t* pwc )
{
	m_str = pwc;
}

Box::Box( char c )
{
	wchar_t wc = 0;
	int nRet = mbtowc( &wc, &c, 1 );

	if( -1 != nRet )
		m_str = wc;
}

Box::Box( wchar_t wc )
{
	m_str = wc;
}
