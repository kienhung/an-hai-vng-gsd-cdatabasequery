#include "StdAfx.h"
#include "CrossfireLauncher.h"



CCrossfireLauncher::CCrossfireLauncher( LPCTSTR strSourcePath, LPCTSTR strLauncherPath )
	:CAutoLauncher(strSourcePath, strLauncherPath)
{

}

CCrossfireLauncher::~CCrossfireLauncher(void)
{
}

BOOL CCrossfireLauncher::Run()
{

	HWND hMainWnd = StartCrossfireLauncher();
	if (NULL == hMainWnd) {
		return FALSE;
	}

	if (FALSE == PressButton(hMainWnd, L"&Tiếp theo >")) {
		return FALSE;
	}

	if (FALSE == SetSourcePath(hMainWnd)) {
		return FALSE;
	}
	return TRUE;
}

HWND CCrossfireLauncher::StartCrossfireLauncher()
{

	if(FALSE == StartLauncherProcess()) {
		return NULL;
	}

	HWND hMainWnd = NULL;
	int iCount = 0;

	TCHAR strClassName[] = L"TWizardForm";
	TCHAR strWndName[] = L"Setup - Đột Kích";

	while (iCount < m_iTimeoutCount) {

		hMainWnd = ::FindWindow(strClassName, strWndName);
		if (hMainWnd != NULL) {
			return hMainWnd;
		}

		iCount++;
		::Sleep(m_iTimeoutSeconds);

	}
	return NULL;
}
/*
BOOL CALLBACK CCrossfireLauncher::FindTiepTheoButtonEnumProc( __in HWND hWnd,__in LPARAM lParam )
{

	TCHAR strWindowText[MAX_PATH];
	::GetWindowText(hWnd, strWindowText, MAX_PATH);

	if (lstrcmp(L"&Tiếp theo >", strWindowText) == 0) {

		::SendMessage(hWnd, BM_CLICK, 0, 0);
		
		CCrossfireLauncher *pLauncher = (CCrossfireLauncher*)lParam;
		pLauncher->m_bResult = TRUE;

		return FALSE;
	}

	return TRUE;
}
*/
BOOL CALLBACK CCrossfireLauncher::FindSourcePathEditEnumProc( HWND hWnd, LPARAM lParam )
{

	const int MAX_LENGTH = 128;
	TCHAR strClassName[MAX_LENGTH];

	::GetClassName(hWnd, strClassName, MAX_LENGTH);

	if (lstrcmpi(strClassName, L"TEdit") == 0) {
	
		CCrossfireLauncher *pLauncher = (CCrossfireLauncher*)lParam;

		::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)pLauncher->m_strSourcePath);
		pLauncher->m_bResult = TRUE;

		return FALSE;
	}

	return TRUE;
}

BOOL CCrossfireLauncher::SetSourcePath( HWND hMainWnd )
{

	int iCount  = 0;

	while (iCount < m_iTimeoutCount) {

		m_bResult = FALSE;

		::EnumChildWindows(hMainWnd, CCrossfireLauncher::FindSourcePathEditEnumProc, (LPARAM)this);

		if (m_bResult == TRUE) {
			return PressButton(hMainWnd, L"&Tiếp theo >");
		}

		iCount++;
		::Sleep(m_iTimeoutSeconds);
	}

	return FALSE;
}

BOOL CCrossfireLauncher::PressTiepTheoButton( HWND hMainWnd )
{
	m_bResult = FALSE;
	m_strButtonName = L"&Tiếp theo >";
	::EnumChildWindows(hMainWnd, CAutoLauncher::FindButtonNameProc, (LPARAM)this);
	return m_bResult;
}
