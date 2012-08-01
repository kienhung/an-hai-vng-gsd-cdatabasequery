#pragma once

class CAutoLauncher
{
protected:
	TCHAR m_strSourcePath[MAX_PATH];
	TCHAR m_strLauncherPath[MAX_PATH];
	HANDLE m_hProcess;

	BOOL m_bResult;
	int m_iTimeoutCount;
	int m_iTimeoutSeconds;

	CString m_strButtonName;

public:
	CAutoLauncher(LPCTSTR strSourcePath, LPCTSTR strLauncherPath);
	virtual ~CAutoLauncher(void);
	virtual BOOL Run() = 0;
	static BOOL CALLBACK FindButtonNameProc(HWND hWnd, LPARAM lParam) ;
protected:
	BOOL StartLauncherProcess();
	BOOL PressButton(HWND hParentWnd, LPCTSTR strButtonName);
};
