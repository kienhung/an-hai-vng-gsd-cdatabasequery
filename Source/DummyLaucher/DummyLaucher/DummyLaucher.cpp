
// DummyLaucher.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DummyLaucher.h"
#include "DummyLaucherDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDummyLaucherApp

BEGIN_MESSAGE_MAP(CDummyLaucherApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDummyLaucherApp construction

CDummyLaucherApp::CDummyLaucherApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDummyLaucherApp object

CDummyLaucherApp theApp;


// CDummyLaucherApp initialization

BOOL CDummyLaucherApp::InitInstance()
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
	
	
	CString strCommand = ::GetCommandLine();
	int iIndex = strCommand.Find(L'@');
	if(iIndex < 0 || iIndex >= strCommand.GetLength())
	{
		return FALSE;
	}
	
	CString strClassName(strCommand);
	strClassName.Delete(0, iIndex + 1);
	strCommand.Delete(iIndex, strCommand.GetLength() - iIndex);
	if(CopyDummyApp(strCommand,strClassName))
	{
		StartProcessDummy(strCommand);
	}
	
	

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
BOOL CDummyLaucherApp::CopyDummyApp(const TCHAR* strPathOldDummy, const TCHAR* strDummyClassName)
{		
	while(TRUE)
	{
		HWND hWndDummy = ::FindWindow(strDummyClassName, NULL);
		if(NULL == hWndDummy)
		{
			break;
		}
	}
	TCHAR strCurrentDir[MAX_PATH] = {0};
	GetModuleFileName(NULL, strCurrentDir, MAX_PATH);
	CString strTemp(strCurrentDir);
	int iIndex = strTemp.ReverseFind(L'\\');
	if(iIndex > 0 && iIndex < strTemp.GetLength())
	{
		strTemp.Delete(iIndex, strTemp.GetLength() - iIndex);
	}
	wmemset(strCurrentDir, 0, MAX_PATH);
	swprintf(strCurrentDir, MAX_PATH, _T("%s\\%s"), strTemp.GetBuffer(), _T("Dummy.exe"));
	
	if(!::CopyFile(strCurrentDir, strPathOldDummy, FALSE))
	{
		DWORD dwError = GetLastError();
		if(dwError == ERROR_ACCESS_DENIED)
		{
			DWORD dwAttr = GetFileAttributes(strPathOldDummy);
			if(dwAttr & FILE_ATTRIBUTE_HIDDEN)
			{
				dwAttr &= ~FILE_ATTRIBUTE_HIDDEN;
			}
			if(dwAttr & FILE_ATTRIBUTE_READONLY)
			{
				dwAttr &= ~FILE_ATTRIBUTE_READONLY;
			}
			if(::CopyFile(strCurrentDir, strPathOldDummy, FALSE))
			{
				return TRUE;
			}
			return FALSE;
		}
	}
	return TRUE;
}
VOID CDummyLaucherApp::StartProcessDummy(const TCHAR* strPathDummy)
{
	BOOL bWorked;
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	CString m_Process(strPathDummy);
	bWorked = ::CreateProcess(strPathDummy,NULL,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi);
}