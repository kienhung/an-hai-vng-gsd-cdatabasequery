#include "StdAfx.h"
#include "LauncherEx.h"
#include "GlobalClass.h"
#include "MyUtils.h"



CLauncherEx::CLauncherEx( LPCTSTR strSource )
:CLauncher(strSource)
{
	ZeroMemory(&m_processInfo, sizeof(PROCESS_INFORMATION));

	CString strConfigDirectory = CGlobalClass::GetInstance()->GetConfigDirectory();

	CString strLauncherConfig;
	strLauncherConfig.Format(L"%s\\%s", strConfigDirectory, L"launcherconfig.xml");

	m_ConfigLoadingResult = m_launcherConfig.load_file(strLauncherConfig);

}

CLauncherEx::~CLauncherEx(void)
{
	ReleaseProcess();

}

BOOL CLauncherEx::StartLauncherProcess()
{
	STARTUPINFO si = { sizeof(si) };

	if (FALSE == ::CreateProcess(m_strLauncher, NULL, NULL, NULL, FALSE, 0, NULL, m_strSource, &si, &m_processInfo)) {
		return FALSE;
	}

	return TRUE;
}

BOOL CLauncherEx::IsWindowShowed( HWND hWnd )
{
	WINDOWPLACEMENT wndpl;
	ZeroMemory(&wndpl, sizeof(WINDOWPLACEMENT));
	
	if (FALSE == ::GetWindowPlacement(hWnd, &wndpl))
		return FALSE;

	if (SW_SHOW == wndpl.showCmd ||
		SW_SHOWNORMAL == wndpl.showCmd ||
		SW_SHOWMAXIMIZED == wndpl.showCmd ||
		SW_RESTORE == wndpl.showCmd)
	{
		return TRUE;
	}
	return FALSE;
}

HWND CLauncherEx::WaitForWindow( LPCTSTR strClassName, LPCTSTR strWindowName, DWORD dwTimeout )
{
	HWND hWnd = NULL;
	DWORD dwStartTime = GetTickCount ();

	while (NULL == hWnd || FALSE == IsWindowShowed(hWnd))
	{
		DWORD dwSpentTime = GetTickCount () - dwStartTime;
		if (dwSpentTime > dwTimeout)
		{
			return NULL;
		}
		hWnd = ::FindWindow(strClassName, strWindowName);
	}
	return hWnd;
}

HWND CLauncherEx::WaitForWindow( LPCTSTR strClassName, LPCTSTR strWindowName, DWORD dwTimeout, DWORD dwLoop )
{
	HWND hWnd = NULL;
	for (DWORD i = 0; i < dwLoop; i++)
	{
		 hWnd = WaitForWindow(strClassName, strWindowName, dwTimeout);
		 if (hWnd != NULL)
		 {
			 return hWnd;
		 }
	}
	return hWnd;
}

HWND CLauncherEx::StartLauncherWindow( LPCTSTR strClassName, LPCTSTR strWindowName )
{
	if(FALSE == StartLauncherProcess()) {
		return NULL;
	}

	DWORD dwWait = 5*60*1000;
	m_hMainWindow = CLauncherEx::WaitForWindow(strClassName,  strWindowName, dwWait);

	return m_hMainWindow;
}

BOOL CLauncherEx::WaitForWindowDisappeared( HWND hWnd, DWORD dwTimeout )
{
	DWORD dwStartTime = GetTickCount ();
	while(IsWindowShowed(hWnd) == TRUE)
	{
		DWORD dwSpentTime = GetTickCount () - dwStartTime;
		if (dwSpentTime > dwTimeout)
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CLauncherEx::ReleaseProcess()
{
	::CloseHandle(m_processInfo.hThread);
	::CloseHandle(m_processInfo.hProcess);
}

CString CLauncherEx::ExtractStringConfig( LPCSTR strGameNode, LPCSTR strChildNode, LPCSTR strAttr )
{
	string strTempUTF8 = m_launcherConfig.child(strGameNode).child(strChildNode).attribute(strAttr).value();
	TCHAR *pTempWidechar =  CMyUtils::ConvertUTF8ToWideChar(strTempUTF8.c_str());
	CString strResult;
	if (pTempWidechar != NULL)
	{
		strResult = CString(pTempWidechar);
		delete[] pTempWidechar;
	}
	return strResult;
}

void CLauncherEx::KillAll()
{
	if (m_hMainWindow != NULL)
	{
		CMyUtils::KillWindowProcess(m_hMainWindow);
	}
	CMyUtils::KillProcess(&m_processInfo);
}
