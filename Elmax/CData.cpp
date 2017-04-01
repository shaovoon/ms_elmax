#include "StdAfx.h"
#include "CData.h"

using namespace Elmax;

CData::CData(void)
	: m_ptrCData(NULL) 
{
}

CData::~CData(void)
{
}

std::wstring CData::GetContent() const
{
	if(!m_ptrCData)
		throw std::runtime_error("Invalid CData object");

	std::wstring data = (LPCWSTR)(m_ptrCData->data);
	return data;
}

long CData::GetLength() const
{
	if(!m_ptrCData)
		throw std::runtime_error("Invalid CData object");

	return m_ptrCData->length;
}

bool CData::Delete()
{
	if(!m_ptrCData)
		throw std::runtime_error("Invalid CData object");

	MSXML2::IXMLDOMNodePtr parent = m_ptrCData->GetparentNode();
	if(parent)
	{
		m_ptrCData = parent->removeChild(m_ptrCData);
	}
	else
		return false;

	return true;
}

bool CData::Update(const std::wstring& data)
{
	if(!m_ptrCData)
		throw std::runtime_error("Invalid CData object");

	HRESULT hr = m_ptrCData->replaceData(0, data.length(), data.c_str());
	return SUCCEEDED(hr);
}

bool CData::IsValid() 
{ 
	if(!m_ptrCData) 
		return false; 

	return true;
}
