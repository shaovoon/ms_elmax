/*
TextOut Library for Native C++ version 1.1.2

Copyright (c) 2007 - 2008 Wong Shao Voon

The Code Project Open License (CPOL)
http://www.codeproject.com/info/cpol10.aspx
*/

#include "stdafx.h"
#include "AbstractTextout.h"


void AbstractTextout::Print( 
	const wchar_t* fmt)
{
	std::wstring wsfmtstr = fmt;

	Process(wsfmtstr);
}

void AbstractTextout::Print( 
	const wchar_t* fmt, 
	Box D1 )
{
	std::wstring wsfmtstr = fmt;

	std::vector<std::wstring> vs;
	vs.push_back( D1.ToString() );

	std::wstring str = StrReplace( wsfmtstr, vs );

	Process(str);
}

void AbstractTextout::Print( 
	const wchar_t* fmt, 
	Box D1, Box D2 )
{
	std::wstring wsfmtstr = fmt;

	std::vector<std::wstring> vs;
	vs.push_back( D1.ToString() );
	vs.push_back( D2.ToString() );

	std::wstring str = StrReplace( wsfmtstr, vs );

	Process(str);
}

void AbstractTextout::Print( 
	const wchar_t* fmt, 
	Box D1, Box D2, Box D3 )
{
	std::wstring wsfmtstr = fmt;

	std::vector<std::wstring> vs;
	vs.push_back( D1.ToString() );
	vs.push_back( D2.ToString() );
	vs.push_back( D3.ToString() );

	std::wstring str = StrReplace( wsfmtstr, vs );

	Process(str);
}

void AbstractTextout::Print( 
	const wchar_t* fmt, 
	Box D1, Box D2, Box D3, Box D4 )
{
	std::wstring wsfmtstr = fmt;

	std::vector<std::wstring> vs;
	vs.push_back( D1.ToString() );
	vs.push_back( D2.ToString() );
	vs.push_back( D3.ToString() );
	vs.push_back( D4.ToString() );

	std::wstring str = StrReplace( wsfmtstr, vs );

	Process(str);
}

void AbstractTextout::Print( 
	const wchar_t* fmt, 
	Box D1, Box D2, Box D3, Box D4, Box D5 )
{
	std::wstring wsfmtstr = fmt;

	std::vector<std::wstring> vs;
	vs.push_back( D1.ToString() );
	vs.push_back( D2.ToString() );
	vs.push_back( D3.ToString() );
	vs.push_back( D4.ToString() );
	vs.push_back( D5.ToString() );

	std::wstring str = StrReplace( wsfmtstr, vs );

	Process(str);
}

void AbstractTextout::Print( 
	const wchar_t* fmt, 
	Box D1, Box D2, Box D3, Box D4, Box D5, Box D6 )
{
	std::wstring wsfmtstr = fmt;

	std::vector<std::wstring> vs;
	vs.push_back( D1.ToString() );
	vs.push_back( D2.ToString() );
	vs.push_back( D3.ToString() );
	vs.push_back( D4.ToString() );
	vs.push_back( D5.ToString() );
	vs.push_back( D6.ToString() );

	std::wstring str = StrReplace( wsfmtstr, vs );

	Process(str);
}

void AbstractTextout::Print( 
	const wchar_t* fmt, 
	Box D1, Box D2, Box D3, Box D4, Box D5, Box D6, Box D7 )
{
	std::wstring wsfmtstr = fmt;

	std::vector<std::wstring> vs;
	vs.push_back( D1.ToString() );
	vs.push_back( D2.ToString() );
	vs.push_back( D3.ToString() );
	vs.push_back( D4.ToString() );
	vs.push_back( D5.ToString() );
	vs.push_back( D6.ToString() );
	vs.push_back( D7.ToString() );

	std::wstring str = StrReplace( wsfmtstr, vs );

	Process(str);
}

void AbstractTextout::Print( 
	const wchar_t* fmt, 
	Box D1, Box D2, Box D3, Box D4, 
	Box D5, Box D6, Box D7, Box D8 )
{
	std::wstring wsfmtstr = fmt;

	std::vector<std::wstring> vs;
	vs.push_back( D1.ToString() );
	vs.push_back( D2.ToString() );
	vs.push_back( D3.ToString() );
	vs.push_back( D4.ToString() );
	vs.push_back( D5.ToString() );
	vs.push_back( D6.ToString() );
	vs.push_back( D7.ToString() );
	vs.push_back( D8.ToString() );

	std::wstring str = StrReplace( wsfmtstr, vs );

	Process(str);
}

void AbstractTextout::Print( 
	const wchar_t* fmt, 
	Box D1, Box D2, Box D3, Box D4, 
	Box D5, Box D6, Box D7, Box D8, Box D9 )
{
	std::wstring wsfmtstr = fmt;

	std::vector<std::wstring> vs;
	vs.push_back( D1.ToString() );
	vs.push_back( D2.ToString() );
	vs.push_back( D3.ToString() );
	vs.push_back( D4.ToString() );
	vs.push_back( D5.ToString() );
	vs.push_back( D6.ToString() );
	vs.push_back( D7.ToString() );
	vs.push_back( D8.ToString() );
	vs.push_back( D9.ToString() );

	std::wstring str = StrReplace( wsfmtstr, vs );

	Process(str);
}

void AbstractTextout::Print( 
	const wchar_t* fmt, 
	Box D1, Box D2, Box D3, Box D4, Box D5, 
	Box D6, Box D7, Box D8, Box D9, Box D10 )
{
	std::wstring wsfmtstr = fmt;

	std::vector<std::wstring> vs;
	vs.push_back( D1.ToString() );
	vs.push_back( D2.ToString() );
	vs.push_back( D3.ToString() );
	vs.push_back( D4.ToString() );
	vs.push_back( D5.ToString() );
	vs.push_back( D6.ToString() );
	vs.push_back( D7.ToString() );
	vs.push_back( D8.ToString() );
	vs.push_back( D9.ToString() );
	vs.push_back( D10.ToString() );

	std::wstring str = StrReplace( wsfmtstr, vs );

	Process(str);
}

std::wstring AbstractTextout::StrReplace( 
	std::wstring& fmtstr, 
	const std::vector<std::wstring>& vs )
{
	size_t pos = 0;
	for( size_t i=0; i<vs.size(); ++i )
	{
		pos = 0;
		std::wstring anchor = StrAnchor( i );
		
		while( std::wstring::npos != pos )
		{
			pos = fmtstr.find( anchor, pos );

			if( std::wstring::npos != pos )
			{
				//fmtstr.replace( pos, 1, vs.at(i) );
				fmtstr.erase( pos, anchor.size() );
				fmtstr.insert( pos, vs.at(i) );
				pos += vs.at(i).size();
			}
		}
	}
	
	return fmtstr;
}

std::wstring AbstractTextout::StrAnchor( size_t i )
{
	std::wstring str = L"{";

	wchar_t buf[20];
	memset( buf, 0, sizeof(buf) );
	errno_t nRet = _itow_s( i, buf, sizeof(buf)/sizeof(wchar_t), 10 );

	if( 0 == nRet )
		str += buf;

	str += L"}";

	return str;
}
