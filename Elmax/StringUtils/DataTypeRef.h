#pragma once
#include <string>

namespace Elmax
{

class DataTypeRef
{
public:
	~DataTypeRef(void);

	union UNIONPTR
	{
		int* pi;
		unsigned int* pui;
		short* psi;
		unsigned short* pusi;
		__int64* pi64;
		unsigned __int64* pui64;
		float* pf;
		double* pd;
		std::string* ps;
		std::wstring* pws;
		char* pc;
		wchar_t* pwc;
	};

	enum DTR_TYPE
	{
		DTR_INT,
		DTR_UINT,
		DTR_SHORT,
		DTR_USHORT,
		DTR_INT64,
		DTR_UINT64,
		DTR_FLOAT,
		DTR_DOUBLE,
		DTR_STR,
		DTR_WSTR,
		DTR_CHAR,
		DTR_WCHAR
	} ;

	DataTypeRef( int& i )					 { m_ptr.pi = &i; m_type = DTR_INT; }

	DataTypeRef( unsigned int& ui )			 { m_ptr.pui = &ui; m_type = DTR_UINT; }

	DataTypeRef( short& si )				 { m_ptr.psi = &si; m_type = DTR_SHORT; }

	DataTypeRef( unsigned short& usi )		 { m_ptr.pusi = &usi; m_type = DTR_USHORT; }

	DataTypeRef( __int64& i64 )				 { m_ptr.pi64 = &i64; m_type = DTR_INT64; }

	DataTypeRef( float& f )					 { m_ptr.pf = &f; m_type = DTR_FLOAT; }

	DataTypeRef( double& d )				 { m_ptr.pd = &d; m_type = DTR_DOUBLE; }

	DataTypeRef( std::string& s )			 { m_ptr.ps = &s; m_type = DTR_STR; }

	DataTypeRef( std::wstring& ws )			 { m_ptr.pws = &ws; m_type = DTR_WSTR; }

	DataTypeRef( char& c )					 { m_ptr.pc = &c; m_type = DTR_CHAR; }

	DataTypeRef( wchar_t& wc )				 { m_ptr.pwc = &wc; m_type = DTR_WCHAR; }

	bool ConvStrToType( const std::string& Str );

	bool ConvStrToType( const std::wstring& Str );

	DTR_TYPE m_type;

	UNIONPTR m_ptr;

};

}