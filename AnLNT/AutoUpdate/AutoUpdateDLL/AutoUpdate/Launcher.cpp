#include "StdAfx.h"
#include "Launcher.h"
#include "MyUtils.h"
#include "GameSourceCompare.h"
#include "MyPath.h"

CLauncher::CLauncher( LPCTSTR strSource )
{
	m_strSource = strSource;

	m_iTimeoutCount = 3600;
	m_iTimeoutSeconds = 1000;

	m_Comparer = NULL;
	//m_dwLauncherTimeOut = 15*60*1000;

	CMyPath path;
	CString strConfFilePath = path.GetExeFilePath() + CString(L"\\conf.ini");
	UINT uiTimeOut = ::GetPrivateProfileInt(L"conf", L"launcherTimeOut", 14, strConfFilePath);
	m_dwLauncherTimeOut = uiTimeOut*60*1000;
}

CLauncher::~CLauncher(void)
{
	if (NULL != m_Comparer)
	{
		delete m_Comparer;
	}
}

BOOL CLauncher::StartLauncherProcess()
{

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	if (FALSE == ::CreateProcess(m_strLauncher, NULL, NULL, NULL, FALSE, 0, NULL, m_strSource, &si, &pi)) {
		return FALSE;
	}

	return TRUE;
}

HWND CLauncher::StartLauncherWindow( LPCTSTR strClassName, LPCTSTR strWindowName )
{

	if(FALSE == StartLauncherProcess()) {
		return NULL;
	}

	m_hMainWindow = NULL;
	int iCount = 0;

	while (iCount < m_iTimeoutCount) {

		m_hMainWindow = ::FindWindow(strClassName, strWindowName);

		if (m_hMainWindow != NULL) {

			::SetWindowPos(m_hMainWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			return m_hMainWindow;
		}

		iCount++;
		::Sleep(m_iTimeoutSeconds);

	}

	return m_hMainWindow;
}

BOOL CLauncher::CheckButton( int iButtonID, WORD wState)
{
	if (FALSE == CheckButton(m_hMainWindow, iButtonID, wState)) {
		return FALSE;
	}

	return TRUE;
}

BOOL CLauncher::CheckButton( HWND hParent, int iButtonID, WORD wState)
{
	::SetWindowPos(m_hMainWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	HWND hWnd = ::GetDlgItem(hParent, iButtonID);

	if (NULL == hWnd) {
		return FALSE;
	} 

	::SendMessage(hWnd, BM_SETCHECK, wState, 0);	
	return TRUE;
}

BOOL CLauncher::ClickButton( int iButtonID )
{

	if (FALSE == ClickButton(m_hMainWindow, iButtonID)) {
		return FALSE;
	}

	return TRUE;
}

BOOL CLauncher::ClickButton( HWND hParent, int iButtonID )
{

	::SetWindowPos(m_hMainWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	HWND hWnd = ::GetDlgItem(hParent, iButtonID);

	if (NULL == hWnd) {
		return FALSE;
	} 

	WORD lParam  = (WORD)hWnd;
	WORD wParam = MAKEWPARAM(iButtonID, BN_CLICKED);

	::SendMessage(hParent, WM_COMMAND, wParam, lParam);
	return TRUE;
}

BOOL CLauncher::CloseWindow( LPCTSTR strClassName, LPCTSTR strWindowName )
{
	HWND hWnd = NULL;
	int iCount = 0;

	while (iCount < m_iTimeoutCount) {

		hWnd  = ::FindWindow(strClassName, strWindowName);

		if (hWnd != NULL) {

			while (hWnd) {
				::PostMessage(hWnd, WM_CLOSE, 0, 0);
				hWnd  = ::FindWindow(strClassName, strWindowName);
			}

			return TRUE;
		}

		iCount++;
		::Sleep(m_iTimeoutSeconds);

	}

	return FALSE;
}

CString CLauncher::GetSourcePath()
{

	return m_strSource;
}


CGameSourceCompare * CLauncher::GetComparer( LPCTSTR strNewSource, LPCTSTR strOldSource )
{
	if (m_Comparer != NULL)
	{
		delete m_Comparer;
	}

	m_Comparer = new CGameSourceCompare(strNewSource, strOldSource);

	if (m_Comparer != NULL)
	{
		return m_Comparer;
	}

	return NULL;
}
