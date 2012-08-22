#include "StdAfx.h"
#include "AuditionAutoLauncher.h"

CAuditionAutoLauncher::CAuditionAutoLauncher(LPCTSTR strSource)
:CLauncher(strSource)
{
	m_strLauncher = strSource + CString(L"\\patcher.exe");

	m_iHCMButtonID = 0x000000B1;
	m_iGoButtonID = 0x000000B4;
	m_iPanelID = 0x000000A8;
	m_iHNButtonID = 0x000000B0;
	m_iCloseButtonID = 0x00000A4;
	m_iTreeCtrlID = 0x00000065;
}

CAuditionAutoLauncher::~CAuditionAutoLauncher(void)
{
}

CString CAuditionAutoLauncher::GetName()
{

	return L"Audition";
}

BOOL CAuditionAutoLauncher::Run()
{

	HWND hMainWnd = StartLauncherWindow(L"GOPLAY", L"goPlay");
	if (NULL == hMainWnd) {
		return FALSE;
	}
	
	if (FALSE == SelectAudition()) {
		return FALSE;
	}

	HWND hPanel = ::GetDlgItem(hMainWnd, m_iPanelID);
	if (NULL == hPanel) {
		return FALSE;
	}

	if (FALSE == CheckButton(hPanel, m_iHCMButtonID)) {
		return FALSE;
	}

	if (FALSE == CheckButton(hPanel, m_iHNButtonID, BST_UNCHECKED)) {
		return FALSE;
	}

	HANDLE hThread = ::CreateThread(NULL, 0, CAuditionAutoLauncher::MonitorThreadFunction, this, 0, NULL);

	if (NULL == hThread) {
		return FALSE;
	}

	if (FALSE == ClickButton(hPanel, m_iGoButtonID)) {
		return FALSE;
	}
	
	::WaitForSingleObject(hThread, INFINITE);
	::CloseHandle(hThread);

	return TRUE;
}

DWORD WINAPI CAuditionAutoLauncher::MonitorThreadFunction( PVOID pvParam )
{
	CAuditionAutoLauncher *pLauncher = (CAuditionAutoLauncher*)pvParam;

	DWORD dwProcessID;
	DWORD dwThreadID = ::GetWindowThreadProcessId(pLauncher->m_hMainWindow, &dwProcessID);

	BOOL isComplete = FALSE;
	int iWaitSeconds = 2000;

	while (FALSE == isComplete) {

		::EnumThreadWindows(dwThreadID, CAuditionAutoLauncher::EnumWindowProc, (LPARAM)&isComplete);

		if (FALSE == isComplete) {
			::Sleep(iWaitSeconds);
		}
	}

	HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);
	::TerminateProcess(hProcess, 0);
	::CloseHandle(hProcess);

	return 0;
}

BOOL CALLBACK CAuditionAutoLauncher::EnumWindowProc( HWND hwnd, LPARAM lParam )
{
	const int MAX_LENGTH = 10;
	TCHAR strClassName[MAX_LENGTH];

	::GetClassName(hwnd, strClassName, MAX_LENGTH);

	if (lstrcmpi(strClassName, L"LoginDlg") == 0) {
			
		BOOL *pIsComplete = (BOOL*)lParam;
		*pIsComplete = TRUE;

		return FALSE;
	}

	return TRUE;
}

BOOL CAuditionAutoLauncher::SelectAudition()
{

	HWND hTreeCtrl = GetDlgItem(m_hMainWindow, m_iTreeCtrlID);
	if (NULL == hTreeCtrl ) {
		return FALSE;
	}

	HTREEITEM hTreeItem = TreeView_GetFirstVisible(hTreeCtrl);
	if (hTreeItem == NULL) {
		return FALSE;
	}

	if (FALSE == TreeView_SelectItem(hTreeCtrl, hTreeItem)) {
		return FALSE;
	}
	return TRUE;
}
