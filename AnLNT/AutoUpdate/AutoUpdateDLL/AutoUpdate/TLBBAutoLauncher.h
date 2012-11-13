#pragma once
#include "launcher.h"

class CTLBBAutoLauncher :
	public CLauncher
{
protected:

	int m_iCloseButtonID;
	int m_iConfirmButtonID;
	int m_iFinishedWhenFailedButtonID;


	int m_iDelayTime;
	BOOL m_bIsFailed;
	BOOL m_bIsComplete;

	CString m_strLoginServerFilePath;
public:
	CTLBBAutoLauncher(LPCTSTR strSource);

	virtual BOOL Run();
	virtual CString GetName();
	virtual ~CTLBBAutoLauncher(void);

	virtual CGameSourceCompare * GetComparer (LPCTSTR strNewSource, LPCTSTR strOldSource);
protected:
	BOOL GetFileWriteTime(DWORD *pLowWriteTime, DWORD *pHighWriteTime);
	BOOL WaitForComplete();
	static DWORD WINAPI MonitorThreadFunction(PVOID pvParam);
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam );
};
