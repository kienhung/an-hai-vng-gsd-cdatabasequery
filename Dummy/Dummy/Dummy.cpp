
// Dummy.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Dummy.h"
#include "DummyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDummyApp

BEGIN_MESSAGE_MAP(CDummyApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDummyApp construction

CDummyApp::CDummyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDummyApp object

CDummyApp theApp;


// CDummyApp initialization

BOOL CDummyApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));



	HKEY hkey;
	LONG lResult;
	lResult = RegOpenKey(HKEY_LOCAL_MACHINE,_T("Software\\Dummy"),&hkey);

	TCHAR szStringValue[2] = {0};
	DWORD dwSize=2;

	if(lResult != ERROR_SUCCESS)
	{
		
		SECURITY_ATTRIBUTES sAttribs = {sizeof(SECURITY_ATTRIBUTES)};
		DWORD dwDisposition=0;
		RegCreateKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Dummy"),0,_T(""),REG_OPTION_VOLATILE,KEY_ALL_ACCESS, &sAttribs, &hkey,&dwDisposition);

		swprintf(szStringValue, 2, _T("1"));
		
		RegSetValueEx(hkey,_T("Register"),0,REG_SZ,(LPBYTE)szStringValue ,sizeof(szStringValue));
		return FALSE;
	}
		
	DWORD dwType=REG_SZ;
	char lszValue[255];
	lResult = RegQueryValueEx(hkey, _T("Register"), NULL, &dwType,(LPBYTE)&lszValue, &dwSize);
	if(lResult == ERROR_SUCCESS)
	{
		if(wcscmp(szStringValue, _T("1")) == 0)
		{
			return TRUE;
		}
		return FALSE;
	}
	
	swprintf(szStringValue, 2, _T("0"));	
	RegSetValueEx(hkey,_T("Register"),0,REG_SZ,(LPBYTE)szStringValue ,sizeof(szStringValue));





	CRegisterInfoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
