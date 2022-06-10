// RootElement.cpp
//
// written by: PJ Arends
// Modified by: Wong Shao Voon
// License Ms-PL

#include "stdafx.h"
#include "RootElement.h"
using namespace Elmax;

bool RootElement::LoadFile(const std::wstring &FilePath)
{
	bool retval(false);

	UnloadFile();

	HRESULT hr = m_ptrDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));

#ifdef _DEBUG
	if (hr == CO_E_NOTINITIALIZED)
	{
		throw std::runtime_error("CoInitialize has not been called for this thread");
	}
#endif

	if (SUCCEEDED(hr))
	{
		retval = true;

		m_ptrDoc->async = VARIANT_FALSE;
		m_ptrDoc->validateOnParse = VARIANT_FALSE;
		m_ptrDoc->resolveExternals = VARIANT_FALSE;

		if (FileExists(FilePath))
		{   // Open existing file
			variant_t varFile(FilePath.c_str());

			// load will fail if the file has malformed xml
			if (m_ptrDoc->load(varFile) != VARIANT_TRUE)
			{
				retval = false;
			}
		}

		if (retval)
		{
			SetDomDoc(m_ptrDoc);
			m_FilePath = FilePath;
		}
	}

	return retval;
}
bool RootElement::CanWriteFile(const std::wstring& FilePath, bool OverWrite, bool CreateFolder)
{
	if (FileExists(FilePath))
	{
		return OverWrite;
	}

	std::wstring Folder = GetFolder(FilePath);

	if (FolderExists(Folder))
	{
		return true;
	}

	if (CreateFolder)
	{
		return CreateDirectory(Folder);
	}

	return false;
}

bool RootElement::SaveFile(const std::wstring& FilePath, bool OverWrite, bool CreateFolder)
{
	if (NULL == m_ptrDoc)
	{
		return false;
	}

	if (!FilePath.empty())
	{
		m_FilePath = FilePath;
	}

	if (CanWriteFile(m_FilePath, OverWrite, CreateFolder))
	{
		variant_t varFile(m_FilePath.c_str());
		Elmax::Document doc(m_ptrDoc);
		return doc.PrettySave(m_FilePath, L"1.0", true);
	}

	return false;
}

bool RootElement::UnloadFile()
{
	m_ptrDoc = NULL;  // calls Release() for us
	m_FilePath.clear();
	return true;
}

RootElement::~RootElement()
{
	UnloadFile();
}

RootElement& RootElement::operator = (const RootElement &other)
{
	UnloadFile();
	Element::operator=(other);
	m_FilePath = other.m_FilePath;

	return *this;
}

bool RootElement::SetFilePath(std::wstring FilePath)
{
	if (NULL == m_ptrDoc)
	{
		return false;
	}

	m_FilePath = FilePath;
	return true;
}

bool RootElement::FileExists(const std::wstring& fileName)
{
	DWORD fileAttr = GetFileAttributes(fileName.c_str());
	if (INVALID_FILE_ATTRIBUTES == fileAttr)
		return false;

	return true;
}

bool RootElement::FolderExists(const std::wstring& Path)
{
	DWORD dwAttrib = GetFileAttributes(Path.c_str());

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

std::wstring RootElement::GetFolder(const std::wstring& FilePath)
{
	std::wstring Folder = L"";
	size_t pos = FilePath.find_last_of(L'\\');
	if(pos!=-1)
		Folder = FilePath.substr(0, pos);

	return Folder;
}

bool RootElement::CreateDirectory(const std::wstring& dd)
{
	HANDLE		fFile;					// File Handle
	WIN32_FIND_DATA fileinfo;			// File Information Structure
	std::vector<std::wstring>	arr;				// CString Array to hold Directory Structures
	BOOL tt;							// BOOL used to test if Create Directory was successful
	size_t x1 = 0;							// Counter
	std::wstring tem = L"";					// Temporary CString Object

	// Before we go to a lot of work.  
	// Does the file exist

	fFile = FindFirstFile(dd.c_str(),&fileinfo);

	// if the file exists and it is a directory
	if(fileinfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		//  Directory Exists close file and return
		FindClose(fFile);
		return TRUE;
	}

	arr.clear();					// Not really necessary - Just habit
	for(x1=0;x1<dd.length();x1++)	// Parse the supplied CString Directory String
	{									
		if(dd.at(x1) != L'\\')		// if the Charachter is not a \ 
			tem += dd.at(x1);		// else add character to Temp String
		else
		{
			arr.push_back(tem);				// if the Character is a \ Add the Temp String to the CString Array
			tem.append(L"\\");				// Now add the \ to the temp string
		}
		if(x1 == dd.length()-1)		// If we reached the end of the file add the remaining string
			arr.push_back(tem);
	}


	// Close the file
	FindClose(fFile);

	// Now lets cycle through the String Array and create each directory in turn
	for(x1 = 1;x1<arr.size();x1++)
	{
		tem = arr[x1];
		tt = ::CreateDirectory(tem.c_str(),NULL);

		// If the Directory exists it will return a false
		if(tt)
			SetFileAttributes(tem.c_str(),FILE_ATTRIBUTE_NORMAL);
		// If we were successful we set the attributes to normal
	}
	arr.clear();
	//  Now lets see if the directory was successfully created
	fFile = FindFirstFile(dd.c_str(),&fileinfo);

	// if the file exists and it is a directory
	if(fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
	{
		//  Directory Exists close file and return
		FindClose(fFile);
		return true;
	}
	else
	{
		FindClose(fFile);
		return false;
	}
}
