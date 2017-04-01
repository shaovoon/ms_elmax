// TryoutDlg.h : header file
//

#pragma once

#include "..\\Elmax\\Element.h"
#include "..\\Elmax\\HyperElement.h"
#include "..\\Elmax\\Document.h"

#include "..\\Elmax\\NewElement.h"
#include "..\\Elmax\\NewAttribute.h"
#include "..\\Elmax\\NewComment.h"
#include "..\\Elmax\\NewCData.h"

// CTryoutDlg dialog
class CTryoutDlg : public CDialog
{
// Construction
public:
	CTryoutDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TRYOUT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HRESULT CreateAndInitDom(MSXML2::IXMLDOMDocumentPtr& pDoc);
	HRESULT OpenDOMFile(MSXML2::IXMLDOMDocumentPtr& pDoc, const std::wstring& szFile);

	bool SaveXml(MSXML2::IXMLDOMDocumentPtr& pDoc, const std::wstring& strFilename);
	bool PrettySaveXml(MSXML2::IXMLDOMDocumentPtr& pDoc, const std::wstring& strFilename);
	bool CreateAndLoadXml(MSXML2::IXMLDOMDocumentPtr& pDoc, const std::wstring& strFilename);
	bool DeleteFile(const std::wstring& strFilename);

	void TestWrite();
	void TestRead();

	void TestWrite2();
	void TestWrite3();
	void TestWrite4();
#if (_MSC_VER >= 1700 )
	void TestWrite5();
#endif

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
