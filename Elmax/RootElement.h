// RootElement.h - Addition for the Elmax XML library
//
// Declares the RootElement class that is derived from the Element class.
// This class manages the connection between XML DOM and the xml file.
// It is intended to be used only as the root of the XML DOM
//
// written by: PJ Arends
// Modified by: Wong Shao Voon
// License: Ms-PL

#pragma once

#include "Element.h"
#include "Document.h"

namespace Elmax
{

	class RootElement : public Element
	{
	private:
		//! XML Document pointer
		//MSXML2::IXMLDOMDocumentPtr m_pDoc;
		//! File path name for the XML document
		std::wstring m_FilePath;

	protected:
		//! Can the file be written to?
		//!
		//! @param FilePath - the fully qualified file and path name for the file
		//! @param OverWrite - true if the existing file can be overwritten
		//! @param CreateFolder - true to create the folders if they are not already there
		//! returns - true if the file can be written to
		bool CanWriteFile(const std::wstring& FilePath, bool OverWrite, bool CreateFolder);

	public:
		//ctors
		//! Default ctor
		//! Loads the supplied file if it exists
		//! creates an empty XML DOM if it does not
		RootElement(const std::wstring& FilePath = L"") { LoadFile(FilePath); }

		//! Copy ctor
		RootElement(const Elmax::RootElement &other) { *this = other; }

		//! dtor
		virtual ~RootElement();

		//! Assignment operator
		RootElement& operator = (const RootElement &other);

		//! equality operator: true if both objects point to the same XML document
		//!                    object even if the file names are different
		bool operator == (const RootElement &other) { return m_ptrDoc == other.m_ptrDoc; }

		//! Load a XML file: return true if successful
		bool LoadFile(const std::wstring& FilePath = L"");

		//! Check if a file is loaded into the object
		bool IsFileLoaded() { return NULL != m_ptrDoc; }

		//! Unload the file from memory - it is NOT saved first
		bool UnloadFile();

		//! Get the path to the XML file
		std::wstring GetFilePath() { return m_FilePath; }

		//! Set a new path for the XML file, returns false if no document is currently loaded
		bool SetFilePath(std::wstring FilePath);

		//! Save the file, specify a new path to change the files name and/or location
		//!
		//! @param FilePath - the fully qualified file and path name for the file
		//! @param OverWrite - true if the existing file can be overwritten
		//! @param CreateFolder - true to create the folders if they are not already there
		//! returns - true if the file was successfully saved
		//!
		bool SaveFile(const std::wstring& FilePath = L"", bool OverWrite = true, bool CreateFolder = false);

	private:
		bool FileExists(const std::wstring& fileName);
		bool FolderExists(const std::wstring& Path);

		std::wstring GetFolder(const std::wstring& FilePath);
		bool CreateDirectory(const std::wstring& dd);

	};

} //namespace Elmax