#include "StdAfx.h"
#include "AuditionLauncher.h"

CAuditionLauncher::CAuditionLauncher(LPCTSTR strSourcePath, LPCTSTR strLauncherPath)
: CCrossfireLauncher(strSourcePath, strLauncherPath)
{
	m_isMonitoring = TRUE;
}

CAuditionLauncher::~CAuditionLauncher(void)
{
}

BOOL CAuditionLauncher::Run()
{

	m_hMainWnd = StartLauncherWindow(L"TWizardForm", L"Setup - Audition");
	if (NULL == m_hMainWnd) {
		return FALSE;
	}

	if (FALSE == PressButton(m_hMainWnd, L"&Tiếp theo >")) {
		return FALSE;
	}

	if (FALSE == SetSourcePath(m_hMainWnd)) {
		return FALSE;
	}

	
	HANDLE hHouseBuyingThread = ::CreateThread(NULL, 0, CAuditionLauncher::MonitorThreadFunction, this, 0, NULL);

	if (FALSE == PressButton(m_hMainWnd, L"&Cài đặt")) {
		return FALSE;
	}

	
	/*
	if (FALSE == PressButton(m_hMainWnd, L"&Kết thúc")) {
		return FALSE;
	}
	*/
	return TRUE;
}

DWORD WINAPI CAuditionLauncher::MonitorThreadFunction( PVOID pvParam )
{
	CAuditionLauncher* pLauncher = (CAuditionLauncher*)pvParam;

	while (TRUE == pLauncher->m_isMonitoring) {
		HWND hActiveWnd = ::GetActiveWindow();

		if (hActiveWnd != pLauncher->m_hMainWnd) {

			TRACE("%d\n", hActiveWnd);
			return 1;

		}
	}
	return 0;
}
