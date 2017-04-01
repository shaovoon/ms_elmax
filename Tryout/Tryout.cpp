// Tryout.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Tryout.h"
#include "TryoutDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTryoutApp

BEGIN_MESSAGE_MAP(CTryoutApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTryoutApp construction

CTryoutApp::CTryoutApp()
{
}


CTryoutApp theApp;


// CTryoutApp initialization

BOOL CTryoutApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	::CoInitialize(NULL);
	{
		CTryoutDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
		}
		else if (nResponse == IDCANCEL)
		{
		}
	}
	::CoUninitialize();

	return FALSE;
}
