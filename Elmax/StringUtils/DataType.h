#pragma once

#include <string>

namespace Elmax
{

class DataType
{
public:
	~DataType(void);

	DataType( int i );

	DataType( unsigned int ui );

	DataType( const __int64& i64 );

	DataType( const unsigned __int64& ui64 );

	DataType( float f );

	DataType( const double& d );

	DataType( const std::string& s );

	DataType( const std::wstring& ws );

	DataType( const char* pc );

	DataType( const wchar_t* pwc );

	DataType( char c );

	DataType( wchar_t wc );

	std::wstring& ToString() { return m_str; }

protected:
	std::wstring m_str;

};

}

