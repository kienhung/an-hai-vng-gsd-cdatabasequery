// AutoUpdateCF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutoUpdateCF.h"
#include "CrossfireLauncher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

BOOL CALLBACK FindTiepTheoButton(__in  HWND hwnd,__in  LPARAM lParam	) {

	TCHAR strWindowText[MAX_PATH];
	::GetWindowText(hwnd, strWindowText, MAX_PATH);
	if (lstrcmp(L"&Tiếp theo >", strWindowText) == 0) {
		::OutputDebugStringA("OK");
	}
	//::GetClassName(hwnd, strWindowText, MAX_PATH);
	::OutputDebugString(strWindowText);
	::OutputDebugStringA("\n");
	//::GetWindowText(hwnd, strWindowText, MAX_PATH);
	//TRACE("%s\n",  strWindowText);
	return TRUE;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		TCHAR strSourcePath[] = L"D:\\GameUpdate\\CrossFire";
		TCHAR strLauncherPath[] = L"D:\\GameUpdate\\CF_Patch_1108.exe";

		CAutoLauncher *pAutoLauncher = new CCrossfireLauncher(strSourcePath, strLauncherPath);
		if (FALSE == pAutoLauncher->Run()) {
			AfxMessageBox(L"Fail", MB_ICONERROR);
		} else {
			AfxMessageBox(L"OK", MB_ICONINFORMATION);
		}


		if (NULL != pAutoLauncher) {
			delete pAutoLauncher;
		}

		//1. Bat cua so update CF
		
		//STARTUPINFO si = { sizeof(si) };
		//PROCESS_INFORMATION pi;
		//TCHAR szCommandLine[] = TEXT("D:\\CF_Patch_1108.exe");

		//CreateProcess(NULL, szCommandLine, NULL, NULL, 
		//	FALSE, 0, NULL, NULL, &si, &pi);
		
		//2. Nhan nut button Tiep Theo

		//HWND hMainWnd = ::FindWindow(L"TWizardForm", L"Setup - Đột Kích");

		//::EnumChildWindows(hMainWnd, FindTiepTheoButton, 0);
		//ASSERT(hBtnTiepTheo);
		/*
		CString strClassName = L"TWizardForm";
		CString strWndName = L"Setup - Đột Kích";
		int iBtnTiepTheoID = 0x00050350;

		CWnd *pWnd = NULL;
		int iCount = 0;

		while (iCount < 3) {
			Sleep(1000);
			pWnd = CWnd::FindWindow(strClassName, strWndName);
			if (NULL != pWnd) {
				break;
			}
			iCount++;
		}

		if (pWnd == NULL) {
			return -1;
		}
	
		CButton *pButton = (CButton*)pWnd->GetDlgItem(iBtnTiepTheoID);

		if (NULL == pButton) {
			TRACE("lay handle button faile");
			return -1;
		}

		WORD lParam  = (WORD)pButton->m_hWnd;
		WORD wParam = MAKEWPARAM(iBtnTiepTheoID, BN_CLICKED);

		pWnd->SendMessage(WM_COMMAND, wParam, lParam);

		//pWnd->SendMessage(WM_CLOSE);
		*/
	}

	return nRetCode;
}
