#pragma once
#include "launcher.h"

class CSilkroadAutoLauncher :
	public CLauncher
{
protected:

	int m_StartButtonID;
	int m_FinishButtonID;

	CString m_strLauncherWindowClassName;
	CString m_strLauncherWindowText;

	BOOL m_bIsFailed;
	BOOL m_bIsComplete;
public:
	CSilkroadAutoLauncher(LPCTSTR strSource);
	virtual ~CSilkroadAutoLauncher(void);

	virtual CString GetName();
	virtual BOOL Run();

	static DWORD WINAPI MonitorThreadFunction(PVOID pvParam);
	static BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam);

protected:
	BOOL WaitForComplete();
};
