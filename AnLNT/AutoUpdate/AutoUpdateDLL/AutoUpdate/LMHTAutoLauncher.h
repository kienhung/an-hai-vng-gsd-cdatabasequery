#pragma once
#include "launcherex.h"

class CLMHTAutoLauncher :
	public CLauncherEx
{
protected:

	BOOL m_bIsInitSuccessful;
	int m_xLoginGarenaButton;
	int m_yLoginGarenaButton;
	int m_xLoginLMHTButton;
	int m_yLoginLMHTButton;

	CString m_strBeforeLoginGarenaWndClass;
	CString m_strBeforeLoginGarenaWndTitle;
	CString m_strAfterLoginGarenaWndClass;
	CString m_strAfterLoginGarenaWndTitle;
	CString m_strLMHTLoginWndClass;
	CString m_strLMHTLoginWndTitle;
	CString m_strLMHTLauncherWndClass;
	CString m_strLMHTLauncherWndTitle;
	CString m_strLastErrorWndClass;
	CString m_strLastErrorWndTitle;

	DWORD m_dwSleep;
	BOOL Init();
protected:
	virtual CString GetName();
	virtual BOOL Run();
public:
	CLMHTAutoLauncher(LPCTSTR strSource);
	virtual ~CLMHTAutoLauncher(void);
	static BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam );
	virtual CGameSourceCompare * GetComparer (LPCTSTR strNewSource, LPCTSTR strOldSource);
};
