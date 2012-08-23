#include "StdAfx.h"
#include "SilkroadAutoLauncher.h"

CSilkroadAutoLauncher::CSilkroadAutoLauncher(LPCTSTR strSource)
:CLauncher(strSource)
{
	m_StartButtonID = 0x000003E8;
	m_FinishButtonID = 0x000003EA;

	m_strLauncher = strSource + CString(L"\\silkroad.exe");

	m_strLauncherWindowClassName = L"#32770";
	m_strLauncherWindowText = L"Silkroad Online Launcher";

	m_bIsFailed = FALSE;
	m_bIsComplete = FALSE;
}

CSilkroadAutoLauncher::~CSilkroadAutoLauncher(void)
{

}

CString CSilkroadAutoLauncher::GetName()
{

	return L"Silkroad";
}

BOOL CSilkroadAutoLauncher::Run()
{

	HWND hMainWnd = StartLauncherWindow(m_strLauncherWindowClassName, m_strLauncherWindowText);
	if (NULL == hMainWnd) {
		return FALSE;
	}

	HANDLE hThread = ::CreateThread(NULL, 0, CSilkroadAutoLauncher::MonitorThreadFunction, this, 0, NULL);
	if (NULL == hThread) {
		return FALSE;
	}

	::CloseHandle(hThread);

	if (FALSE == WaitForComplete()) {
		return FALSE;
	}

	return TRUE;
}

BOOL CSilkroadAutoLauncher::WaitForComplete()
{

	DWORD dwDelayTime = 5000;

	while (FALSE == m_bIsComplete && m_bIsFailed == FALSE) {

		HWND hMainWnd = FindWindow(m_strLauncherWindowClassName, m_strLauncherWindowText);

		if (NULL != hMainWnd) {

			HWND hStartButtonID = ::GetDlgItem(hMainWnd, m_StartButtonID);

			if (TRUE == ::IsWindowVisible(hStartButtonID)) {

				m_bIsComplete = TRUE;
			
				if (FALSE == ClickButton(hMainWnd, m_FinishButtonID)) {
					return FALSE;
				}

			} 
		}
		::Sleep(dwDelayTime);
	}

	if (TRUE == m_bIsFailed) {
		return FALSE;
	}

	return TRUE;
}

DWORD WINAPI CSilkroadAutoLauncher::MonitorThreadFunction( PVOID pvParam )
{
	CSilkroadAutoLauncher *pLauncher = (CSilkroadAutoLauncher*)pvParam;

	if (NULL == pLauncher) {
		return FALSE;
	}

	while (FALSE == pLauncher->m_bIsComplete && FALSE ==  pLauncher->m_bIsFailed ) {

		EnumWindows(CSilkroadAutoLauncher::EnumWindowProc, (LPARAM)pLauncher);

	}

	return TRUE;
}

BOOL CALLBACK CSilkroadAutoLauncher::EnumWindowProc( HWND hwnd, LPARAM lParam )
{

	const int MAX_LENGTH = 20;

	TCHAR strClassName[MAX_LENGTH];
	TCHAR strWindowName[MAX_LENGTH];

	::GetClassName(hwnd, strClassName, MAX_LENGTH);
	::GetWindowText(hwnd, strWindowName, MAX_LENGTH);

	if (lstrcmpi(strClassName, L"#32770") == 0 && lstrcmpi(strWindowName, L"Silkroad Online") == 0) {

		CSilkroadAutoLauncher *pLauncher = (CSilkroadAutoLauncher*)lParam;

		DWORD dwMainWndProcessID;
		DWORD dwErrorDlgProcessID;

		::GetWindowThreadProcessId(pLauncher->m_hMainWindow, &dwMainWndProcessID);
		::GetWindowThreadProcessId(hwnd, &dwErrorDlgProcessID);

		if (dwErrorDlgProcessID == dwMainWndProcessID) {

			pLauncher->ClickButton(pLauncher->m_hMainWindow, pLauncher->m_FinishButtonID);
			pLauncher->m_bIsFailed = TRUE;	

			return FALSE;
		}
	}

	return TRUE;
}
