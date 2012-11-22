#include "StdAfx.h"
#include "WindowFinder.h"

CWindowFinder::CWindowFinder(void)
{
}

CWindowFinder::~CWindowFinder(void)
{
}

BOOL CALLBACK CWindowFinder::EnumWindowsProc( HWND hwnd, LPARAM lParam )
{
	const int MAX_LENGTH = 256;

	TCHAR strClassName[MAX_LENGTH] = {0};
	TCHAR strWindowName[MAX_LENGTH] = {0};

	::GetClassName(hwnd, strClassName, MAX_LENGTH);
	::GetWindowText(hwnd, strWindowName, MAX_LENGTH);

	CWindowFinder *pFinder = (CWindowFinder *)lParam;

	if (lstrcmpi(strClassName, pFinder->m_strClassName) == 0 && lstrcmpi(strWindowName, pFinder->m_strWindowName) == 0)
	{
		pFinder->m_vResultWnd.push_back(hwnd);

	}
	return TRUE;
}

vector<HWND> CWindowFinder::GetListWindow( LPCTSTR strClassName, LPCTSTR strWindowName )
{
	m_strClassName = strClassName;
	m_strWindowName = strWindowName;

	m_vResultWnd.clear();
	EnumWindows(EnumWindowsProc, (LPARAM)this);

	return m_vResultWnd;
}
