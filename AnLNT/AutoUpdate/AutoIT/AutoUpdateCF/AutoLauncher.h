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
	CString m_strCheckboxName;

public:
	CAutoLauncher(LPCTSTR strSourcePath, LPCTSTR strLauncherPath);
	virtual ~CAutoLauncher(void);
	virtual BOOL Run() = 0;
	virtual CString GetName() = 0;

	CString GetSourcePath();
	CString GetLauncherPath();

	static BOOL CALLBACK FindButtonNameProc(HWND hWnd, LPARAM lParam) ;

protected:

	BOOL StartLauncherProcess();
	HWND StartLauncherWindow(LPCTSTR strClassName, LPCTSTR strWindowName);
	BOOL PressButton(HWND hParentWnd, LPCTSTR strButtonName);
	BOOL CloseWindow(LPCTSTR strClassName, LPCTSTR strWindowName);
};
