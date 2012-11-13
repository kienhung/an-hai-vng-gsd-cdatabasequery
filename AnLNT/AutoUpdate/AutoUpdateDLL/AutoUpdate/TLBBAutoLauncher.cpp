#include "StdAfx.h"
#include "TLBBAutoLauncher.h"
#include "MyUtils.h"
#include "TLBBCompare.h"

CTLBBAutoLauncher::CTLBBAutoLauncher(LPCTSTR strSource)
:CLauncher(strSource)
{
	m_strLauncher = strSource + CString(L"\\Launch.exe");

	m_iCloseButtonID = 1027;
	m_iConfirmButtonID = 0x00000411;
	m_iFinishedWhenFailedButtonID = 0x00000001;

	m_iDelayTime = 5000;

	m_bIsFailed = FALSE;
	m_bIsComplete = FALSE;

	m_strLoginServerFilePath = m_strSource + L"\\Patch\\loginserver.txt";
}

CTLBBAutoLauncher::~CTLBBAutoLauncher(void)
{
}

CString CTLBBAutoLauncher::GetName()
{

	return L"TLBB";
}

BOOL CTLBBAutoLauncher::Run()
{
	if (CMyUtils::FileExists(m_strLoginServerFilePath) == TRUE)
	{
		if (CMyUtils::DeleteFile(m_strLoginServerFilePath) == FALSE)
		{
			CMyUtils::WriteLog(L"TO delete serverlogin file is failed");
			return FALSE;
		}
	}

	HWND hMainWnd = StartLauncherWindow(L"#32770", L"TLBB2");

	if (NULL == hMainWnd) {
		return FALSE;
	}

	HANDLE hThread = ::CreateThread(NULL, 0, CTLBBAutoLauncher::MonitorThreadFunction, this, 0, NULL);

	if (NULL == hThread) {
		return FALSE;
	}

	::CloseHandle(hThread);
	
	if (FALSE == WaitForComplete()) {
		return FALSE;
	}

	EnumWindows(CTLBBAutoLauncher::EnumWindowsProc, (LPARAM)this);

	if (FALSE == ClickButton(m_hMainWindow, m_iCloseButtonID)) {
		return FALSE;
	}

	if (TRUE == m_bIsFailed) {
		return FALSE;
	}
	return TRUE;
}

BOOL CTLBBAutoLauncher::WaitForComplete()
{
	while (FALSE == m_bIsComplete && FALSE == m_bIsFailed) {
		if (CMyUtils::FileExists(m_strLoginServerFilePath) == TRUE)
		{
			m_bIsComplete = TRUE;
		}			
		::Sleep(m_iDelayTime);
	}
	return TRUE;
}

DWORD WINAPI CTLBBAutoLauncher::MonitorThreadFunction( PVOID pvParam )
{

	CTLBBAutoLauncher *pLauncher = (CTLBBAutoLauncher*)pvParam;

	DWORD dwStartTime = GetTickCount ();

	while(FALSE == pLauncher->m_bIsFailed && FALSE == pLauncher->m_bIsComplete) {

		DWORD dwEndTime = GetTickCount () - dwStartTime ;
	
		if (dwEndTime > pLauncher->m_dwLauncherTimeOut)
		{
			pLauncher->m_bIsFailed = TRUE;
			CMyUtils::WriteLog(L"TLBB Launcher timeout");

			return TRUE;
		}

		EnumWindows(CTLBBAutoLauncher::EnumWindowsProc, (LPARAM)pLauncher);
	}

	return 0;
}

BOOL CALLBACK CTLBBAutoLauncher::EnumWindowsProc( HWND hwnd, LPARAM lParam )
{

	const int MAX_LENGTH = 7;

	TCHAR strClassName[MAX_LENGTH];
	TCHAR strWindowName[MAX_LENGTH];

	::GetClassName(hwnd, strClassName, MAX_LENGTH);
	::GetWindowText(hwnd, strWindowName, MAX_LENGTH);

	CTLBBAutoLauncher *pLauncher = (CTLBBAutoLauncher*)lParam;

	if (0 == lstrcmpi(strClassName, L"#32770") && GetParent(hwnd) == pLauncher->m_hMainWindow) {

		if (0 == lstrcmpi(strWindowName, L"TLBB2")) {

			if (FALSE == pLauncher->ClickButton(hwnd, pLauncher->m_iConfirmButtonID)) {
				CMyUtils::WriteLog(L"To click cofirmation button is failed");
			}

			pLauncher->m_bIsFailed = TRUE;
		}

		if (0 == lstrcmpi(strWindowName, L"????")) {
			if (FALSE == pLauncher->ClickButton(hwnd, pLauncher->m_iFinishedWhenFailedButtonID)) {
				CMyUtils::WriteLog(L"To click finish button is failed");
			}
			pLauncher->m_bIsFailed = TRUE;
		}

		return FALSE;
	}

	return TRUE;
}

CGameSourceCompare * CTLBBAutoLauncher::GetComparer( LPCTSTR strNewSource, LPCTSTR strOldSource )
{
	if (m_Comparer != NULL)
	{
		delete m_Comparer;
	}

	m_Comparer = new CTLBBCompare(strNewSource, strOldSource);

	if (m_Comparer != NULL)
	{
		return m_Comparer;
	}

	return NULL;
}
