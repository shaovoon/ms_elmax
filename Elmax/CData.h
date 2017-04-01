#pragma once


namespace Elmax
{
//! Class to access XML CData Section
class CData
{
friend class Element;
private:
	//! Constructor
	CData(void);
	//! Non-default Constructor
	CData(MSXML2::IXMLDOMCDATASectionPtr ptrCData) : m_ptrCData(ptrCData) {};

public:
#if _HAS_CPP0X
	//! Copy Constructor
	CData(CData& other) : m_ptrCData(other.m_ptrCData) {};
#endif
	//! Destructor
	~CData(void);

	//! Get the CDataSection data
	std::wstring GetContent() const;
	//! Get the length of the CDataSection data in wchar_t size
	long GetLength() const;
	//! Delete itself
	bool Delete();
	//! Update the CDataSection
	bool Update(const std::wstring& data);
	//! Is valid?
	bool IsValid(); 

private:
	//! CDataSection object
	MSXML2::IXMLDOMCDATASectionPtr m_ptrCData;
};

} // ns Elmax