#include "StdAfx.h"
#include "AutoLauncher.h"
#include <strsafe.h>


CAutoLauncher::CAutoLauncher( LPCTSTR strSourcePath, LPCTSTR strLauncherPath )
{
	StringCchCopy(m_strSourcePath, MAX_PATH, strSourcePath);
	StringCchCopy(m_strLauncherPath, MAX_PATH, strLauncherPath);
	m_hProcess = NULL;
	m_bResult = FALSE;

	m_iTimeoutCount = 10;
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

	::OutputDebugString(strWindowText);
	::OutputDebugStringA("\n");

	CAutoLauncher *pLauncher = (CAutoLauncher*)lParam;

	if (lstrcmp(pLauncher->m_strButtonName, strWindowText) == 0) {

		::SendMessage(hWnd, BM_CLICK, 0, 0);
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
