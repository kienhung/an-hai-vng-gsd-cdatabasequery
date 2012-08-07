#include "StdAfx.h"
#include "AutoLauncher.h"
#include <strsafe.h>


CAutoLauncher::CAutoLauncher( LPCTSTR strSourcePath, LPCTSTR strLauncherPath )
{
	StringCchCopy(m_strSourcePath, MAX_PATH, strSourcePath);
	StringCchCopy(m_strLauncherPath, MAX_PATH, strLauncherPath);
	m_hProcess = NULL;
	m_bResult = FALSE;

	m_iTimeoutCount = 3600;
	m_iTimeoutSeconds = 1000;
}

CAutoLauncher::~CAutoLauncher(void)
{
}

BOOL CAutoLauncher::StartLauncherProcess()
{

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	if (FALSE == ::CreateProcess(NULL, m_strLauncherPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		return FALSE;
	}

	m_hProcess = pi.hProcess;
	return TRUE;
}

BOOL CALLBACK CAutoLauncher::FindButtonNameProc( HWND hWnd, LPARAM lParam )
{

	TCHAR strWindowText[MAX_PATH];
	::GetWindowText(hWnd, strWindowText, MAX_PATH);

	CAutoLauncher *pLauncher = (CAutoLauncher*)lParam;

	if (lstrcmp(pLauncher->m_strButtonName, strWindowText) == 0) {

		WORD lParam  = (WORD)hWnd;
		WORD wParam = MAKEWPARAM(::GetDlgCtrlID(hWnd), BN_CLICKED);

		HWND hParent = ::GetParent(hWnd);

		::SetWindowPos(hParent, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		::SendMessage(hParent, WM_COMMAND, wParam, lParam);

		pLauncher->m_bResult = TRUE;
		return FALSE;
	}

	return TRUE;
}

BOOL CAutoLauncher::PressButton( HWND hParentWnd, LPCTSTR strButtonName )
{
	m_bResult = FALSE;
	m_strButtonName = strButtonName;
	::EnumChildWindows(hParentWnd, CAutoLauncher::FindButtonNameProc, (LPARAM)this);
	return m_bResult;
}



BOOL CAutoLauncher::CloseWindow( LPCTSTR strClassName, LPCTSTR strWindowName )
{

	HWND hMainWnd = NULL;
	int iCount = 0;

	while (iCount < m_iTimeoutCount) {

		hMainWnd = ::FindWindow(strClassName, strWindowName);

		if (hMainWnd != NULL) {
			::SendMessage(hMainWnd, WM_CLOSE, 0, 0);
			return TRUE;
		}

		iCount++;
		::Sleep(m_iTimeoutSeconds);

	}
	return FALSE;
}

HWND CAutoLauncher::StartLauncherWindow( LPCTSTR strClassName, LPCTSTR strWindowName )
{
	if(FALSE == StartLauncherProcess()) {
		return NULL;
	}

	HWND hMainWnd = NULL;
	int iCount = 0;

	while (iCount < m_iTimeoutCount) {

		hMainWnd = ::FindWindow(strClassName, strWindowName);

		if (hMainWnd != NULL) {

			::SetWindowPos(hMainWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			return hMainWnd;
		}

		iCount++;
		::Sleep(m_iTimeoutSeconds);

	}
	return NULL;
}

CString CAutoLauncher::GetSourcePath()
{
	return m_strSourcePath;
}

CString CAutoLauncher::GetLauncherPath()
{
	return m_strLauncherPath;
}
