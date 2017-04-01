/// @file UnicodeFile.h
///
/// @brief Program to read and write Unicode files
///
/// @author Wong Shao Voon
///
/// @copyright Copyright © <em><b>muvee Technologies</b></em> Pte Ltd 2006
/// All Rights Reserved 



#include <cstdlib>
#include <cstdio>
#include <string>

#ifndef		_UNICODEFILE_H_ 
#define		_UNICODEFILE_H_

/// class to read and write Unicode files
class CUnicodeFile
{
public:
	/// Constructor 
	CUnicodeFile() : 
		m_bFirstWrite(false),
		m_bFirstRead(false),
		m_pFile(NULL), 
		m_pszReadAll(NULL), 
		m_posReadAll(0), 
		m_dwFileSize(0)
		{};
	
	/// Destructor 
	~CUnicodeFile() { Close(); };

	/// Open a file
	///
	/// @param pszFileName	file name in ascii characters
	/// @param mode			file open mode(same as fopen)
	/// @return true if successful
	bool Open( const char* pszFileName, const char* mode );
	
	/// Open a file
	///
	/// @param pszFileName	file name in wide characters
	/// @param mode			file open mode(same as wfopen)
	/// @return true if successful
	bool Open( const wchar_t* pszFileName, const wchar_t* mode );

	/// Test if an opened file is a Unicode file
	///
	/// @return true if it is a little endian unicode file
	bool IsUnicodeFile();

	/// Test if an opened file is a UTF8 file
	///
	/// @return true if it is a UTF8 file
	bool IsUtf8File();

	/// Write to a file
	///
	/// @param pszContents	A pointer to a wide char array terminated by null
	/// @return true if successful
	bool Write( const std::wstring& pszContents );

	/// Write to a file
	///
	/// @param pszContents	A pointer to a wide char array terminated by null
	/// @return true if successful
	bool Write( const wchar_t* pszContents );

	/// Write to a file
	///
	/// @param pszContents	A pointer to a wide char array
	/// @param nBufLen		The length of wide chars to be written
	/// @return true if successful
	bool Write( const wchar_t* pszContents, int nBufLen );
	
	/// Write UTF16 BOM to a file
	bool WriteUtf16Bom();

	/// Write UTF8 BOM to a file
	bool WriteUtf8Bom();

	/// Write UTF8 to a file
	///
	/// @param pszContents	A pointer to a wide char array terminated by null
	/// @return true if successful
	bool WriteUtf8( const std::wstring& pszContents );

	/// Write a line to a file and append a newline
	///
	/// @param szContents	A string to be written
	/// @return true if successful
	bool WriteLine( const std::wstring& szContents );

	/// Write a line to a file and append a newline
	///
	/// @param pszContents	A pointer to a wide char array terminated by null
	/// @return true if successful
	bool WriteLine( const wchar_t* pszContents );

	/// Write a line to a file and append a newline
	///
	/// @param pszContents	A pointer to a wide char array
	/// @param nBufLen		The length of wide chars to be written
	/// @return true if successful
	bool WriteLine( const wchar_t* pszContents, int nBufLen );

	/// Read number of wide chars and the pointer must be deleted by caller
	/// using delete [] if it returns true(successful)
	///
	/// @param pszContents	A reference to pointer to a wide char array
	/// @param nBufLen		The length of wide chars to read successfully
	/// @return true if successful
	bool Read( wchar_t*& pszContents, int& nBufLen );
	
	/// Read the whole file and retrieve the contents with ReadLine()
	/// Must be called once before any ReadLine()
	///
	/// @return true if successful
	bool ReadAll();

	/// Read the whole UTF8 file and convert them to Unicode 
	/// and retrieve the contents with ReadLine()
	///
	/// @return true if successful
	bool ReadAllUtf8();

	/// Read a line and the pointer must be deleted by caller
	/// using delete [] if it returns true(successful)
	///
	/// @param szContents	A wide char string
	/// @param nBufLen		The length of wide chars to read successfully
	/// @return true if successful
	bool ReadLine( std::wstring& szContents );

	/// Read a line and the pointer must be deleted by caller
	/// using delete [] if it returns true(successful)
	///
	/// @param pszContents	A reference to pointer to a wide char array
	/// @param nBufLen		The length of wide chars to read successfully
	/// @return true if successful
	bool ReadLine( wchar_t*& pszContents, int& nBufLen );

	/// Flush the writes to the file
	///
	/// @return true if successful
	bool Flush();

	/// Close file handle
	///
	/// @return true if successful
	bool Close();

	/// Get file size
	///
	/// @param szFile		File name in ascii chars
	/// @param BufSize		Logical file size
	/// @return true if successful
	bool GetFileSize( const char* szFile, DWORD& BufSize );
	
	/// Get file size
	///
	/// @param szFile		File name in wide chars
	/// @param BufSize		Logical file size
	/// @return true if successful
	bool GetFileSize( const wchar_t* szFile, DWORD& BufSize );

	/// Convert wide string to UTF8
	///
	/// @param wstr			String to be converted
	/// @param pChar		Must be deleted [] by user when returned true
	/// @param nBufLen		Store length of the buffer
	/// @return true if successful
	bool WideToUtf8( const std::wstring& wstr, char*& pChar, int& nBufLen );

	/// Convert UTF8 to wide string
	///
	/// @param pChar		Char array to be converted
	/// @param nBufLen		Length of the buffer
	/// @param wstr			String to store the converted wide string
	/// @return true if successful
	bool Utf8ToWide( const char* pChar, int nBufLen, std::wstring& wstr );

	/// Convert UTF8 to wide char array
	///
	/// @param pChar		Char array to be converted
	/// @param nBufLen		Length of the buffer
	/// @param pDest		Array to store the converted wide string
	/// @param DestLen		Length of the pDest array in wide characters, not bytes.
	/// @return true if successful
	bool Utf8ToWide( const char* pChar, int nBufLen, wchar_t*& pDest, int& DestLen );

protected:
	/// Converts any \r\n to \n
	///
	/// @param pszSource	Source contents read straight from file
	/// @param nSource		Length of the contents in wide chars
	/// @param pszDest		Pointer to destination array
	/// @param nDest		Length of the converted contents in wide chars
	/// @return true if successful
	bool FileToContents( 
		const wchar_t* pszSource, 
		int nSource, 
		wchar_t*& pszDest,
		int& nDest	);

	/// Converts any \n to \r\n
	///
	/// @param pszSource	Source contents read straight from file
	/// @param nSource		Length of the contents in wide chars
	/// @param pszDest		Pointer to destination array
	/// @param nDest		Length of the converted contents in wide chars
	/// @return true if successful
	bool ContentsToFile( 
		const wchar_t* pszSource, 
		int nSource, 
		wchar_t*& pszDest,
		int& nDest	);

private:
	/// The first time it is written.
	/// Basically is to ignore the file id
	bool m_bFirstWrite;

	/// The first time it is read.
	/// Basically is to ignore the file id
	bool m_bFirstRead;

	/// File handle
	FILE* m_pFile;

	/// Pointer to store all the contents ReadAll() read.
	wchar_t *m_pszReadAll;

	// The file pointer position
	int m_posReadAll;

	/// The logical file size
	DWORD m_dwFileSize;



};


#endif //	_UNICODEFILE_H_