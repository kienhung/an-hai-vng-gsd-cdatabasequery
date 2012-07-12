
// QuanLy.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "QuanLy.h"
#include "QuanLyDlg.h"
#include "KetNoiDlg.h"
#include "StringConverter.h"
#include "MySQLDataAccessHelper.h"
#include <initguid.h>


#include <direct.h> // for getcwd
#include <stdlib.h>// for MAX_PATH
#pragma warning(disable: 4996)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQuanLyApp


class CQuanLyModule :
	public CAtlMfcModule
{
public:
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_QUANLY, "{3AECA472-660B-4833-90E6-7FA76874A780}");};

CQuanLyModule _AtlModule;

BEGIN_MESSAGE_MAP(CQuanLyApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CQuanLyApp construction

CQuanLyApp::CQuanLyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CQuanLyApp object

CQuanLyApp theApp;


// CQuanLyApp initialization

BOOL CQuanLyApp::InitInstance()
{
	AfxOleInit();
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
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// Register class factories via CoRegisterClassObject().
	if (FAILED(_AtlModule.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE)))
		return FALSE;
	#endif // !defined(_WIN32_WCE) || defined(_CE_DCOM)
	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Don't show the main window
		return TRUE;
	}
	// App was launched with /Unregserver or /Unregister switch.
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		_AtlModule.UpdateRegistryAppId(FALSE);
		_AtlModule.UnregisterServer(TRUE);
		return FALSE;
	}
	// App was launched with /Register or /Regserver switch.
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
	{
		_AtlModule.UpdateRegistryAppId(TRUE);
		_AtlModule.RegisterServer(TRUE);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	if(!ConnectString.m_bIsConnected)
	{
		while(true)
		{
			CKetNoiDlg* dlgKetNoi = new CKetNoiDlg();
			INT_PTR iRes = dlgKetNoi->DoModal();
			if(iRes == IDOK)
			{
				if(Connect())
				{
					
					break;
				}
				else
				{
					MessageBox(NULL, _T("that bai"), _T("thong bao"), 0);
					
				}
			}
			else if(iRes == IDCANCEL)
			{
				
				return FALSE;
			}

		}
	}
	CQuanLyDlg dlg;
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
bool CQuanLyApp::Connect()
{
	char *path = NULL;
	size_t size = 0;
	path= getcwd(path,size);
	strcat(path, "\\ketnoi.dat");
	CStringConverter Convert;
	CFile cfile_KetNoi;
	
	
	cfile_KetNoi.Open(Convert.UTF8ToUnicode(path), CFile::modeCreate| CFile::modeReadWrite);
	try
	{
		cfile_KetNoi.Read(&ConnectString, sizeof(ConnectString));
		if(!ConnectString.m_bIsConnected)
		{
			if(CMySQLDataAccessHelper::CheckUser(ConnectString.m_strUsername,
											ConnectString.m_strPasssword, 
											ConnectString.m_strServerAddress, 
											ConnectString.m_strDatabaseName))
			{
				cfile_KetNoi.Close();
				return true;
			}
			else
			{
				cfile_KetNoi.Close();
				return false;
			}
			
		}
		//cfile_KetNoi.Write(&ConnectString, sizeof(ConnectString));
	}catch(CFileException ex)
	{	
		if(cfile_KetNoi != NULL)
			cfile_KetNoi.Close();
		return false;
	}
	cfile_KetNoi.Close();
	return false;
}
BOOL CQuanLyApp::ExitInstance(void)
{
#if !defined(_WIN32_WCE) || defined(_CE_DCOM)
	_AtlModule.RevokeClassObjects();
#endif
	return CWinApp::ExitInstance();
}
