#pragma once
namespace Elmax
{
//! Class to access XML comment
class Comment
{
friend class Element;
private:
	//! Constructor
	Comment(void);
	//! Non-default Constructor
	Comment(MSXML2::IXMLDOMCommentPtr ptrComment) : m_ptrComment(ptrComment) {};

public:
#if _HAS_CPP0X
	//! Copy Constructor
	Comment(Comment& other) : m_ptrComment(other.m_ptrComment) {};
#endif
	//! Destructor
	~Comment(void);

	//! Get the Comment data
	std::wstring GetContent() const;
	//! Get the length of the Comment in wchar_t size
	long GetLength() const;
	//! Delete itself
	bool Delete();
	//! Update the Comment
	bool Update(const std::wstring& comment);
	//! Is valid?
	bool IsValid();

private:
	//! Comment object
	MSXML2::IXMLDOMCommentPtr m_ptrComment;
};

} // ns Elmax