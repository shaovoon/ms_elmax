#include "stdafx.h"
#include "UnicodeFile.h"
#include <vector>

#define VECTOR_RESERVE		50000

bool CUnicodeFile::Open( const char* pszFileName, const char* mode )
{
	// check if already open then close first, before opening
	if( m_pFile )
	{
		CUnicodeFile::Close();
		m_pFile = NULL;
	}
	
	GetFileSize( pszFileName,  m_dwFileSize );

	fopen_s(&m_pFile, pszFileName, mode );

	if( !m_pFile )
		return false;

	m_bFirstWrite = true;

	m_bFirstRead = true;

	return true;
}


bool CUnicodeFile::Open( const wchar_t* pszFileName, const wchar_t* mode  )
{
	// check if already open then close first, before opening
	if( m_pFile )
	{
		CUnicodeFile::Close();
		m_pFile = NULL;
	}
	
	GetFileSize( pszFileName,  m_dwFileSize );

	_wfopen_s(&m_pFile, pszFileName, mode );

	if( !m_pFile )
		return false;

	m_bFirstWrite = true;

	m_bFirstRead = true;

	return true;
}


// Must be called right after open
// Used before reading file
bool CUnicodeFile::IsUnicodeFile()
{
	if( !m_pFile )
		return false;

	m_bFirstRead = false;

	unsigned char tt[2] = {0,0};
	
	fseek( m_pFile, 0, SEEK_SET );

	fread( tt, 1, 2, m_pFile );

	if( tt[0] != 0xff || tt[1] != 0xfe )
	{
		fseek( m_pFile, 0, SEEK_SET );
		
		m_bFirstRead = true;

		return false; // not a unicode file
	}

	return true;
}


bool CUnicodeFile::IsUtf8File()
{
	if( !m_pFile )
		return false;

	m_bFirstRead = false;

	unsigned char tt[3] = {0,0,0};
	
	fseek( m_pFile, 0, SEEK_SET );

	fread( tt, 1, 3, m_pFile );

	if( tt[0] != 0xEF || tt[1] != 0xBB || tt[2] != 0xBF )
	{
		fseek( m_pFile, 0, SEEK_SET );
		
		m_bFirstRead = true;

		return false; // not a UTF8 file
	}

	return true;
}


bool CUnicodeFile::Write( const std::wstring& szContents )
{
	return Write( szContents.c_str() );
}


bool CUnicodeFile::Write( const wchar_t* pszContents )
{
	if( !m_pFile )
		return false;

//	return Write( pszContents, wcslen( pszContents ) * sizeof(wchar_t) );
	return Write( pszContents, wcslen( pszContents ) );
}


bool CUnicodeFile::Write( const wchar_t* pszContents, int nBufLen )
{
	if( !m_pFile )
		return false;

	if( m_bFirstWrite )
	{
		unsigned char tt[2] = { 0xff, 0xfe };
		fwrite( tt, 1, 2, m_pFile );
		m_bFirstWrite = false;
	}

	wchar_t* pszDest = NULL;
	int nDest = 0;
		
	bool bRet = ContentsToFile( pszContents, nBufLen, pszDest, nDest );

	if( !bRet )
	{
		if( pszDest )
		{
			delete [] pszDest;
			pszDest = NULL;
		}
		return false;
	}

	if( pszDest )
	{
		fwrite( pszDest, 2, nDest, m_pFile );
		delete [] pszDest;
		pszDest = 0;
	}

	return true;
}

bool CUnicodeFile::WriteUtf16Bom()
{
	if( !m_pFile )
		return false;

	unsigned char bom[2] = { 0xFE, 0xFF };

	fwrite( bom, 1, 2, m_pFile );

	return true;
}

bool CUnicodeFile::WriteUtf8Bom()
{
	if( !m_pFile )
		return false;

	unsigned char bom[3] = { 0xEF, 0xBB, 0xBF };

	fwrite( bom, 1, 3, m_pFile );

	return true;
}


bool CUnicodeFile::WriteUtf8( const std::wstring& szContents )
{
	if( !m_pFile )
		return false;

	if( szContents == L"" )
		return true;

	char* pChar = 0;
	int len = 0;
	if( WideToUtf8( szContents, pChar, len ) )
	{
		if( pChar && len > 0 )
		{
			fwrite( pChar, 1, len-1, m_pFile );
			delete [] pChar;
		}
	}

	return true;
}


bool CUnicodeFile::WriteLine( const std::wstring& szContents )
{
	return WriteLine( szContents.c_str() );
}


bool CUnicodeFile::WriteLine( const wchar_t* pszContents )
{
	if( !m_pFile )
		return false;

	return WriteLine( pszContents, 0 );
}


bool CUnicodeFile::WriteLine( const wchar_t* pszContents, int nBufLen )
{
	if( !m_pFile )
		return false;

	if( 0 == nBufLen )
	{
		nBufLen = wcslen( pszContents );
	}

	wchar_t* pszBuf = new wchar_t[nBufLen];


	if( !pszBuf )
		return false;

	memcpy(pszBuf, pszContents, nBufLen*2 );
	
	bool bRet = Write( pszBuf, nBufLen );
	
	bRet = Write( L"\n", 1 );

	delete [] pszBuf;

	return bRet;
}


bool CUnicodeFile::Read( wchar_t*& pszContents, int& nBufLen )
{
	if( !m_pFile )
		return false;

	if( m_bFirstRead )
	{
		m_bFirstRead = false;

		unsigned char tt[2] = {0,0};
		fread( tt, 1, 2, m_pFile );

		if( tt[0] != 0xff || tt[1] != 0xfe )
		{
			fseek( m_pFile, 0, SEEK_SET );
			
			m_bFirstRead = true;

			return false; // not a unicode file
		}
	}



	wchar_t* pszBuf = new wchar_t[nBufLen];

	int nBufLen2 = fread( pszBuf, 2, nBufLen,m_pFile );

	wchar_t* pszDest = NULL;
	int nDest = 0;

	bool bRet = FileToContents(	pszBuf, nBufLen2, pszDest, nDest );

	delete [] pszBuf;
	pszBuf = NULL;

	if( !bRet )
	{
		if( pszDest )
		{
			delete [] pszDest;
			pszDest = NULL;
		}
		return false;
	}

	if( pszDest )
	{	
		pszContents = pszDest;
		nBufLen = nDest;
	}

	return true;
}


// Read all and store them in a buffer.
// To be used together as ReadLine()
bool CUnicodeFile::ReadAll()
{
	if( !m_pFile )
		return false;

	if( m_pszReadAll )
		delete [] m_pszReadAll;

	if( m_bFirstRead )
	{
		m_bFirstRead = false;
		
		unsigned char tt[2] = {0,0};
		fread( tt, 1, 2, m_pFile );

		if( tt[0] != 0xff || tt[1] != 0xfe )
		{
			fseek( m_pFile, 0, SEEK_SET );
			
			m_bFirstRead = true;

			return false; // not a unicode file
		}
	}

	if( m_dwFileSize )
		m_pszReadAll = new wchar_t[m_dwFileSize/2-1];

	if( !m_pszReadAll )
		return false;

	if( 0 == (m_dwFileSize%2) )
		memset( m_pszReadAll, 0, m_dwFileSize-2 );
	else
		memset( m_pszReadAll, 0, m_dwFileSize-3 );

	if( m_pszReadAll )
	{
		DWORD dwReadSize = fread( m_pszReadAll, 2, m_dwFileSize/2-1, m_pFile ); 

		if( dwReadSize != m_dwFileSize/2-1 )
		{
			//TRACE(L"Reading file size different!\n");
			return false;
		}
	}

/*
	if( m_pszReadAll )
	{
		unsigned int TotalRead=0;
		unsigned int ReadSize=0;
		do
		{
			ReadSize = fread( m_pszReadAll, 2, (m_dwFileSize/2-1)-TotalRead, m_pFile ); 
			TotalRead += ReadSize;

			if(ferror(m_pFile))
				break;

			if(feof(m_pFile))
				break;
		}
		while( ReadSize );
	}
*/
	return true;
}


// Read all and store them in a buffer.
// To be used together as ReadLine()
bool CUnicodeFile::ReadAllUtf8()
{
	if( !m_pFile )
		return false;

	if( m_pszReadAll )
		delete [] m_pszReadAll;

	if( m_bFirstRead )
	{
		m_bFirstRead = false;

		unsigned char tt[3] = {0,0,0};
		fread( tt, 1, 3, m_pFile );

		if( tt[0] != 0xEF || tt[1] != 0xBB || tt[2] != 0xBF )
		{
			fseek( m_pFile, 0, SEEK_SET );
			
			m_bFirstRead = true;

			return false; // not a utf8 file
		}
	}

	char* pszReadAll = 0;
	if( m_dwFileSize )
		pszReadAll = new char[m_dwFileSize-3];

	if( !pszReadAll )
		return false;

	memset( pszReadAll, 0, m_dwFileSize-3 );

	if( pszReadAll )
	{
		DWORD dwReadSize = fread( pszReadAll, 1, m_dwFileSize-3, m_pFile ); 

		if( dwReadSize != m_dwFileSize-3 )
		{
			//TRACE(L"Reading file size different!\n");
			//return false;
		}

		std::wstring szDest;
		int DestLen = 0;
		if( Utf8ToWide( pszReadAll, dwReadSize, m_pszReadAll, DestLen ) )
		{
			delete [] pszReadAll;
			m_dwFileSize = DestLen*2+2;
		}
		else 
			return false;

	}

	return true;
}


bool CUnicodeFile::ReadLine( std::wstring& szContents )
{
	wchar_t* pszContents = 0;
	int nBufLen = 0;
	bool bRet = ReadLine( pszContents, nBufLen );
	
	if( bRet && pszContents )
	{
		szContents = pszContents;
		delete [] pszContents;
		return true;
	}
	
	return false;
}


bool CUnicodeFile::ReadLine( wchar_t*& pszContents, int& nBufLen )
{
	if( !m_pFile )
		return false;

	if( (unsigned int)m_posReadAll >= m_dwFileSize/2-1 )
		return false;

	if( m_pszReadAll )
	{
		using namespace std;
		vector<wchar_t> vwc;

		vwc.reserve( VECTOR_RESERVE );

		DWORD dwBufSize = m_dwFileSize/2-1;
		DWORD dw = 0;
		for( dw=m_posReadAll; dw<dwBufSize; ++dw )
		{
			if( dw+1<dwBufSize && L'\r' == m_pszReadAll[dw] && L'\n' == m_pszReadAll[dw+1] )
			{
				++dw;
				++dw;
				break;
			}
			else
				vwc.push_back( m_pszReadAll[dw] );
		}

		m_posReadAll = dw;

//		if( !vwc.empty() )
//			vwc.push_back( L'\0' );
//		else
//			return false;

		vwc.push_back( L'\0' );

		pszContents = new wchar_t[vwc.size()];

		if( !pszContents )
			return false;

		nBufLen = vwc.size();
		for( int i=0; i<nBufLen; ++i )
		{
			pszContents[i] = vwc[i];
		}
	}
	else
		return false;

	return true;
}


bool CUnicodeFile::Flush()
{
	int nRet = EOF;
	if( m_pFile )
	{
		nRet = fflush( m_pFile );
	}

	bool bRet = false;
	
	if( !nRet )
		bRet = true;
	else 
		bRet = false;

	return bRet; 
}


bool CUnicodeFile::Close()
{
	int nRet = EOF; // 0 is success and EOF fails
	
	if( m_pszReadAll )
	{
		delete [] m_pszReadAll;
		m_pszReadAll = NULL;
	}
	
	if( m_pFile )
	{
		nRet = fclose( m_pFile );
		m_pFile = NULL;
	}

	bool bRet = false;
	
	if( !nRet )
		bRet = true;
	else 
		bRet = false;

	return bRet; 
}


bool CUnicodeFile::FileToContents( 
	const wchar_t* pszSource, 
	int nSource, 
	wchar_t*& pszDest,
	int& nDest	)
{
	if( !pszSource )
		return false;

	std::vector<wchar_t> vwc;
	vwc.reserve( VECTOR_RESERVE );

	if( 0 == nSource )
	{
		const wchar_t* pszSource2 = pszSource;

		while( pszSource2 )
		{
			if( L'\r' == *pszSource2 && L'\n' == *(pszSource2+1) )
			{
				vwc.push_back( L'\n' );
				pszSource2++;
			}
			else
				vwc.push_back( *pszSource2 );

			pszSource2++;
		}
	}
	else
	{
		for( int i=0; i<nSource; ++i )
		{
			if( i+1 < nSource && L'\r' == pszSource[i] && L'\n' == pszSource[i+1] )
			{
				vwc.push_back( L'\n' );
				++i;
			}
			else
				vwc.push_back( pszSource[i] );
		}
	}

	if( !vwc.empty() )
		vwc.push_back( L'\0' );
	else
		return false;

	pszDest = new wchar_t[vwc.size()];

	if( !pszDest )
		return false;

	nDest = vwc.size();
	for( int i=0; i<nDest; ++i )
	{
		pszDest[i] = vwc[i];
	}

	return true;
}


bool CUnicodeFile::ContentsToFile( 
	const wchar_t* pszSource, 
	int nSource, 
	wchar_t*& pszDest,
	int& nDest	)
{
	if( !pszSource )
		return false;

	std::vector<wchar_t> vwc;
	vwc.reserve( VECTOR_RESERVE );

	if( 0 == nSource )
	{
		const wchar_t* pszSource2 = pszSource;

		while( pszSource2 )
		{
			if( L'\n' == *pszSource2 )
			{
				vwc.push_back( L'\r' );
				vwc.push_back( L'\n' );
			}
			else
				vwc.push_back( *pszSource2 );
	
			pszSource2++;
		}
	}
	else
	{
		for( int i=0; i<nSource; ++i )
		{
			if( L'\n' == pszSource[i] )
			{
				vwc.push_back( L'\r' );
				vwc.push_back( L'\n' );
			}
			else
				vwc.push_back( pszSource[i] );
		}
	}

	pszDest = new wchar_t[vwc.size()];

	if( !pszDest )
		return false;

	nDest = vwc.size();
	for( int i=0; i<nDest; ++i )
	{
		pszDest[i] = vwc[i];
	}

	return true;
}


bool CUnicodeFile::GetFileSize( const char* szFile,  DWORD& BufSize )
{
	HANDLE hFile = CreateFileA(
		szFile,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL );

	if( INVALID_HANDLE_VALUE == hFile )
	{
		// File cannot be opened!
		return false;
	}
	

	LARGE_INTEGER FileSize;
	BOOL bSuccess2 = GetFileSizeEx(
	  hFile,    
	  &FileSize );

	if( !bSuccess2 )
	{
		// Cannot get file size!
		CloseHandle( hFile );

		return false;
	}

	CloseHandle( hFile );

	BufSize = FileSize.LowPart;

	return true;
}


bool CUnicodeFile::GetFileSize( const wchar_t* szFile,  DWORD& BufSize )
{
	HANDLE hFile = CreateFileW(
		szFile,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL );

	if( INVALID_HANDLE_VALUE == hFile )
	{
		// File cannot be opened!
		return false;
	}
	

	LARGE_INTEGER FileSize;
	BOOL bSuccess2 = GetFileSizeEx(
	  hFile,    
	  &FileSize );

	if( !bSuccess2 )
	{
		// Cannot get file size!
		CloseHandle( hFile );

		return false;
	}

	CloseHandle( hFile );

	BufSize = FileSize.LowPart;

	return true;
}


bool CUnicodeFile::WideToUtf8( const std::wstring& wstr, char*& pChar, int& nBufLen )
{
	char* pBuf = 0;

	int nRet = WideCharToMultiByte(
	  CP_UTF8,
	  0,
	  wstr.c_str(),
	  -1,
	  pBuf, // pBuf not used here
	  0,
	  NULL,
	  NULL );

	if( !nRet )
		return false;

	++nRet;
	pBuf = new char[nRet];

	if( !pBuf )
		return false;

	ZeroMemory( pBuf, nRet );

	nRet = WideCharToMultiByte(
	  CP_UTF8,
	  0,
	  wstr.c_str(),
	  -1,
	  pBuf, // pBuf not used here
	  nRet,
	  NULL,
	  NULL );
	
	if( nRet )
	{
		pChar = pBuf;
		nBufLen = nRet;
		return true;
	}
	
	delete [] pBuf;

	return false;
}


bool CUnicodeFile::Utf8ToWide( const char* pChar, int nBufLen, std::wstring& wstr )
{
	if( !pChar )
		return false;
	
	wchar_t* pBuf = 0;

	int nRet = MultiByteToWideChar(
	  CP_UTF8,
	  0,
	  pChar,
	  nBufLen,
	  pBuf, // pBuf not used here
	  0 );

	if( !nRet )
		return false;

	++nRet;
	pBuf = new wchar_t[nRet];

	if( !pBuf )
		return false;

	ZeroMemory( pBuf, nRet*sizeof(wchar_t) );

	nRet = MultiByteToWideChar(
	  CP_UTF8,
	  0,
	  pChar,
	  nBufLen,
	  pBuf, // pBuf not used here
	  nRet);
	
	if( nRet )
	{
		wstr = pBuf;
		delete [] pBuf;
		return true;
	}
	
	delete [] pBuf;

	return false;
}


bool CUnicodeFile::Utf8ToWide( const char* pChar, int nBufLen, wchar_t*& pDest, int& DestLen )
{
	if( !pChar )
		return false;
	
	wchar_t* pBuf = 0;

	int nRet = MultiByteToWideChar(
	  CP_UTF8,
	  0,
	  pChar,
	  nBufLen,
	  pBuf, // pBuf not used here
	  0 );

	if( !nRet )
		return false;

	++nRet;
	pBuf = new wchar_t[nRet];

	if( !pBuf )
		return false;

	ZeroMemory( pBuf, nRet*sizeof(wchar_t) );

	nRet = MultiByteToWideChar(
	  CP_UTF8,
	  0,
	  pChar,
	  nBufLen,
	  pBuf, // pBuf not used here
	  nRet);
	
	if( nRet )
	{
		pDest = pBuf;
		DestLen = nRet;
		return true;
	}
	
	return false;
}
