#include "StdAfx.h"
#include "CrossfireAutoLauncher.h"

#include <tlhelp32.h>

CCrossfireAutoLauncher::CCrossfireAutoLauncher(LPCTSTR strSource)
:CLauncher(strSource)
{
	m_strLauncher = strSource + CString(L"\\Crossfire.exe");

	m_iStartButtonID = 0x000003E8;
	m_iOkButtonID = 0x00000002;

	m_bIsFailed = FALSE;

}

CCrossfireAutoLauncher::~CCrossfireAutoLauncher(void)
{
}

CString CCrossfireAutoLauncher::GetName()
{

	return L"Crossfire";
}

BOOL CCrossfireAutoLauncher::Run()
{

	HWND hMainWnd = StartLauncherWindow(L"#32770", L"Crossfire");
	if (NULL == hMainWnd) {
		return FALSE;
	}

	if (FALSE == ClickButton(hMainWnd, m_iStartButtonID)) {
		return FALSE;
	}

	HANDLE hThread = ::CreateThread(NULL, 0, CCrossfireAutoLauncher::MonitorThreadFunction, this, 0, NULL);

	if (NULL == hThread) {
		return FALSE;
	}

	::WaitForSingleObject(hThread, INFINITE);
	::CloseHandle(hThread);

	if (TRUE == m_bIsFailed) {
		return FALSE;
	}

	return TRUE;
}



BOOL CCrossfireAutoLauncher::WaitForComplete()
{

	HWND hGameWindow = ::FindWindow(L"Crossfire", L"Crossfire");
	if (NULL == hGameWindow) {
		return FALSE;
	}

	DWORD dwProcessID;

	GetWindowThreadProcessId(hGameWindow, &dwProcessID);

	HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);

	if (NULL == hProcess) {
		_tprintf(L"Open process is failed. Error: %d\n", GetLastError());
		return TRUE;
	}
	
	if (FALSE == ::TerminateProcess(hProcess, 0)) {
		_tprintf(L"Termiate process is failed. Error: %d\n", GetLastError());
		return TRUE;
	} 

	::CloseHandle(hProcess);

	return TRUE;
	
}

DWORD WINAPI CCrossfireAutoLauncher::MonitorThreadFunction( PVOID pvParam )
{

	CCrossfireAutoLauncher* pLaucher = (CCrossfireAutoLauncher*)pvParam;

	while(FALSE == pLaucher->WaitForComplete() && FALSE == pLaucher->m_bIsFailed) {
		EnumWindows( CCrossfireAutoLauncher::EnumWindowsProc, (LPARAM)pvParam );
	}

	return TRUE;
}

BOOL CALLBACK CCrossfireAutoLauncher::EnumWindowsProc( HWND hwnd, LPARAM lParam )
{

	const int MAX_LENGTH = 31;

	TCHAR strClassName[MAX_LENGTH];
	TCHAR strWindowName[MAX_LENGTH];

	::GetClassName(hwnd, strClassName, MAX_LENGTH);
	::GetWindowText(hwnd, strWindowName, MAX_LENGTH);

	if (lstrcmpi(strClassName, L"#32770") == 0 && lstrcmpi(strWindowName, L"Đột Kích - Trong tầm ngắm v28") == 0) {

		BOOL bIsErrorDlgFound = FALSE;

		::EnumChildWindows(hwnd, CCrossfireAutoLauncher::EnumChildWindowsProc, (LPARAM)&bIsErrorDlgFound);

		if (TRUE == bIsErrorDlgFound) {
			
			CCrossfireAutoLauncher* pLaucher = (CCrossfireAutoLauncher*)lParam;
			pLaucher->m_bIsFailed = TRUE;

			pLaucher->m_hMainWindow = hwnd;
			pLaucher->ClickButton(pLaucher->m_hMainWindow, pLaucher->m_iOkButtonID);
		}
	}

	return TRUE;
}

BOOL CALLBACK CCrossfireAutoLauncher::EnumChildWindowsProc( HWND hwnd, LPARAM lParam )
{
	
	const int MAX_LENGTH = 26;

	TCHAR strWindowName[MAX_LENGTH];
	::GetWindowText(hwnd, strWindowName, MAX_LENGTH);

	if (lstrcmpi(strWindowName, L"Không thể tải version.ini") == 0) {

		BOOL *pbIsErrorDlgFound = (BOOL *)lParam;
		*pbIsErrorDlgFound = TRUE;
	}

	return TRUE;

}
