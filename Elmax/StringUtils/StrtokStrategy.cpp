/*
String Split Library for Native C++ 1.1

Copyright (c) 2007 - 2008 Wong Shao Voon

The Code Project Open License (CPOL)
http://www.codeproject.com/info/cpol10.aspx
*/
#include "StdAfx.h"
#include "StrtokStrategy.h"

///////////////////////
///////////////////////
// StrtokStrategyW member functions

size_t StrtokStrategy::Extract( 
	const std::wstring& StrToExtract, 
	std::vector<Elmax::DataTypeRef*> vecDTR )
{
	std::vector<std::wstring> vecSplit;
	const size_t size = StrToExtract.size()+1;
	wchar_t* pszToExtract = new wchar_t[size];
	wmemset( pszToExtract, 0, size );
	wcscpy_s( pszToExtract, size, StrToExtract.c_str() );

	wchar_t *pszContext = 0;
	wchar_t *pszSplit = 0;
	pszSplit = wcstok_s( pszToExtract, m_sDelimit.c_str(), &pszContext );

	while( NULL != pszSplit )
	{
		vecSplit.push_back(std::wstring( pszSplit ) );
		
		pszSplit = wcstok_s( NULL, m_sDelimit.c_str(), &pszContext );
	}

	delete [] pszToExtract;

	size_t fail = 0;
	for( size_t i=0; i<vecDTR.size(); ++i )
	{
		if( i < vecSplit.size() )
		{
			if( false == vecDTR[i]->ConvStrToType( vecSplit[i] ) )
				++fail;
		}
		else
			break;
	}

	return vecSplit.size()-fail;
}
