#pragma once
#include "launcherex.h"

class CGAPAutoLauncher :
	public CLauncherEx
{
protected:

	BOOL m_bIsInitSuccessful;
	BOOL m_bIsStopToFindWindow;
	BOOL m_bHasUpdate;

	CString m_strUpdateManagerWndClass;
	CString m_strUpdateManagerWndTitle;
	CString m_strGarenaMessengerWndClass;
	CString m_strGarenaMessangerWndTitle;

	int m_iXUpdateOKButton;
	int m_iYUpdateOKBUtton;
	int m_iXExecuteUpdateButton;
	int m_iYExecuteUpdateButton;

	DWORD m_dwWaitForUpdateManagerAppearedTime;
	DWORD m_dwWaitForUpdateManagerAppearedTry;
	DWORD m_dwWaitForUpdateManagerDisappearedTime;
	DWORD m_dwWaitForUpdateManagerDisappearedTry;

protected:
	BOOL Init();

public:
	CGAPAutoLauncher(LPCTSTR strSource);
	virtual ~CGAPAutoLauncher(void);

	virtual CString GetName();
	virtual BOOL Run();

	static DWORD WINAPI FindUpdateManagerThreadFunction(PVOID pvParam);
	static DWORD WINAPI FindGarenaMessengerThreadFunction(PVOID pvParam);
};
