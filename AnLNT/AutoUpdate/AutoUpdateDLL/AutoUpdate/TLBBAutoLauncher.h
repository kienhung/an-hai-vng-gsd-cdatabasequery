#pragma once
#include "launcher.h"

class CTLBBAutoLauncher :
	public CLauncher
{
protected:

	int m_iCloseButtonID;
	int m_iConfirmButtonID;
	int m_iFinishedWhenFailedButtonID;

	DWORD m_LoginServerFileLowWriteTime;
	DWORD m_LoginServerFileHighWriteTime;

	int m_iDelayTime;
	BOOL m_bIsFailed;
	BOOL m_bIsComplete;

public:
	CTLBBAutoLauncher(LPCTSTR strSource);

	virtual BOOL Run();
	virtual CString GetName();
	virtual ~CTLBBAutoLauncher(void);
	virtual BOOL Compare(LPCTSTR strSourcePath, LPCTSTR strTempSourcePath);

protected:
	BOOL GetLoginServerFileWriteTime(DWORD *pLowWriteTime, DWORD *pHighWriteTime);
	BOOL WaitForComplete();
	static DWORD WINAPI MonitorThreadFunction(PVOID pvParam);
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam );
};
