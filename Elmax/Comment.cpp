#include "StdAfx.h"
#include "Comment.h"


using namespace Elmax;

Comment::Comment(void)
: m_ptrComment(NULL) 
{
}

Comment::~Comment(void)
{
}

std::wstring Comment::GetContent() const
{
	if(!m_ptrComment)
		throw std::runtime_error("Invalid comment object");

	std::wstring comment = (LPCWSTR)(m_ptrComment->data);

	return comment;
}

long Comment::GetLength() const
{
	if(!m_ptrComment)
		throw std::runtime_error("Invalid comment object");

	return m_ptrComment->length;
}

bool Comment::Delete()
{
	if(!m_ptrComment)
		throw std::runtime_error("Invalid comment object");

	MSXML2::IXMLDOMNodePtr parent = m_ptrComment->GetparentNode();
	if(parent)
	{
		m_ptrComment = parent->removeChild(m_ptrComment);
	}
	else
		return false;

	return true;
}

bool Comment::Update(const std::wstring& data)
{
	if(!m_ptrComment)
		throw std::runtime_error("Invalid comment");

	HRESULT hr = m_ptrComment->replaceData(0, data.length(), data.c_str());
	return SUCCEEDED(hr);
}

bool Comment::IsValid() 
{ 
	if(!m_ptrComment) 
		return false; 
	
	return true;
}
