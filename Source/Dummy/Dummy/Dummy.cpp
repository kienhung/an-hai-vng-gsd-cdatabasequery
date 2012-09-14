// Dummy.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Dummy.h"
#include "DummyDlg.h"
#include "DummyUpdater.h"
#include "MyUtils.h"
#include "AppUtility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDummyApp

BEGIN_MESSAGE_MAP(CDummyApp, CWinApp)
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

	CString strAppVersion;
	strAppVersion.LoadString(IDS_APP_VERSION);

	AfxMessageBox(strAppVersion);

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));



	RunOnlyOneInst();

	CAppUtility appUtility;
	if(!appUtility.CheckCSMExist())
	{
		return FALSE;
	}
	
	m_strMachineCode = CMyUtils::GetMachineCode();


	//CDummyUpdater dummyUpdater;
	//if (TRUE == dummyUpdater.IsNeedUpdate())

	//{
	//	if (TRUE == dummyUpdater.StartUpdate())
	//	{
	//		return FALSE;
	//	}
	//}
	
	if (!ReregisterDialogClass())
		return FALSE;

	CDummyDlg dlg;
	m_pMainWnd = &dlg;
#if 0
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
#else
	dlg.Create(CDummyDlg::IDD);
	if (dlg.m_hWnd)
	{
		dlg.ShowWindow(SW_HIDE);
	}
	else
	{
		return FALSE;
	}

	
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	dlg.DestroyWindow();
#endif

//	// Since the dialog has been closed, return FALSE so that we exit the
//	//  application, rather than start the application's message pump.
	return FALSE;
}

int CDummyApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

	CloseHandle(m_hMutex);
	return CWinApp::ExitInstance();
}

void CDummyApp::RunOnlyOneInst()
{
	CString strAppName, strClassName;
	
	strAppName.LoadString(IDS_APP_NAME_MUTEX);
	strClassName.LoadString(IDS_APP_CLASS_NAME);
	m_hMutex = CreateMutex(NULL, FALSE, strAppName);

	if (m_hMutex == NULL)
	{
		AfxMessageBox(_T("System error!"));
		exit(1);
	}
	else if (GetLastError() == ERROR_ALREADY_EXISTS) 
	{
		// There is an instance of App is running. Exit program!
		// Foreground and activates the window before exit
		CWnd	*pWnd;
		pWnd = CWnd::FindWindow(strClassName, NULL);
		if (pWnd) 
		{
			if (pWnd->IsWindowVisible())
			{
				if (pWnd->IsIconic())
					pWnd->ShowWindow(SW_RESTORE);
			}
			else
			{
				//pWnd->PostMessage(WM_COMMAND, IDM_REGISTER_INFO, 0);
				pWnd->PostMessage(WM_CHECK_SHOW_REGISTER_INFO);
			}		
		}

		CloseHandle(m_hMutex);
		exit(0);
	}	
}

BOOL CDummyApp::ReregisterDialogClass()
{
	WNDCLASS wc = {0};
	CString strClassName;

	strClassName.LoadString(IDS_APP_CLASS_NAME);

	// Get the info for this class.
	// #32770 is the default class name for dialogs boxes.
	if (!::GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wc))
	{
		return FALSE;
	}

	// Change the name of the class.
	wc.lpszClassName = strClassName.GetBuffer(strClassName.GetLength());
	// Register this class so that MFC can use it.
	if (!AfxRegisterClass(&wc))
	{
		return FALSE;
	}

	return TRUE;
}
CString CDummyApp::GetMachineCode()
{
	return m_strMachineCode;
}