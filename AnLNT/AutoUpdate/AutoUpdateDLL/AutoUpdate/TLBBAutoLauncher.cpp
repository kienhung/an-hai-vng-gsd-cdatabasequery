#include "StdAfx.h"
#include "TLBBAutoLauncher.h"

CTLBBAutoLauncher::CTLBBAutoLauncher(LPCTSTR strSource)
:CLauncher(strSource)
{
	m_strLauncher = strSource + CString(L"\\Launch.exe");

	m_iCloseButtonID = 1027;
	m_iConfirmButtonID = 0x00000411;

	m_iDelayTime = 5000;

	m_bIsFailed = FALSE;
	m_bIsComplete = FALSE;
}

CTLBBAutoLauncher::~CTLBBAutoLauncher(void)
{
}

CString CTLBBAutoLauncher::GetName()
{

	return L"Thien Long Bat Bo";
}

BOOL CTLBBAutoLauncher::Run()
{
	HWND hMainWnd = StartLauncherWindow(L"#32770", L"TLBB2");

	if (NULL == hMainWnd) {
		return FALSE;
	}

	if (FALSE == GetLoginServerFileWriteTime(&m_LoginServerFileLowWriteTime, &m_LoginServerFileHighWriteTime)) {
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

	if (FALSE == ClickButton(m_hMainWindow, m_iCloseButtonID)) {
		return FALSE;
	}

	if (TRUE == m_bIsFailed) {
		return FALSE;
	}

	return TRUE;
}

BOOL CTLBBAutoLauncher::GetLoginServerFileWriteTime( DWORD *pLowWriteTime, DWORD *pHighWriteTime )
{

	CString strLoginServerFilePath = m_strSource + L"\\Patch\\LoginServer.txt";

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = ::FindFirstFile(strLoginServerFilePath, &FindFileData);

	if (INVALID_HANDLE_VALUE == hFind) {
		return FALSE;
	}

	*pLowWriteTime = FindFileData.ftLastWriteTime.dwLowDateTime;
	*pHighWriteTime = FindFileData.ftLastWriteTime.dwHighDateTime;

	::FindClose(hFind);

	return TRUE;
}

BOOL CTLBBAutoLauncher::WaitForComplete()
{

	DWORD dwNewLoginServerFileLowWriteTime;
	DWORD dwNewLoginServerFileHighWriteTime;

	while (FALSE == m_bIsComplete && FALSE == m_bIsFailed) {

		if (FALSE == GetLoginServerFileWriteTime(&dwNewLoginServerFileLowWriteTime, &dwNewLoginServerFileHighWriteTime)) {
			return FALSE;
		}

		if (m_LoginServerFileLowWriteTime != dwNewLoginServerFileLowWriteTime || m_LoginServerFileHighWriteTime != dwNewLoginServerFileHighWriteTime) {
			m_bIsComplete = TRUE;
		}

		::Sleep(m_iDelayTime);
	}

	return TRUE;
}

DWORD WINAPI CTLBBAutoLauncher::MonitorThreadFunction( PVOID pvParam )
{

	CTLBBAutoLauncher *pLauncher = (CTLBBAutoLauncher*)pvParam;

	while(FALSE == pLauncher->m_bIsFailed && FALSE == pLauncher->m_bIsComplete) {

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

	if (lstrcmpi(strWindowName, L"TLBB2") == 0 && lstrcmpi(strClassName, L"#32770") == 0) {

		CTLBBAutoLauncher *pLauncher = (CTLBBAutoLauncher*)lParam;

		if (GetParent(hwnd) == pLauncher->m_hMainWindow) {

			pLauncher->m_bIsFailed = TRUE;

			if (FALSE == pLauncher->ClickButton(hwnd, pLauncher->m_iConfirmButtonID)) {
				printf("nhan button xac nhan that bai\n");
			}
		}
		
	}

	return TRUE;
}
