#pragma once
#include "launcher.h"

class CCrossfireAutoLauncher :
	public CLauncher
{
protected:
	int m_iStartButtonID;
	int m_iOkButtonID;
	BOOL m_bIsFailed;

	BOOL WaitForComplete();
public:
	CCrossfireAutoLauncher(LPCTSTR strSource);
	virtual ~CCrossfireAutoLauncher(void);

	virtual CString GetName();
	virtual BOOL Run();

	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam );
	static BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam );
	static DWORD WINAPI MonitorThreadFunction(PVOID pvParam);

	virtual CGameSourceCompare * GetComparer (LPCTSTR strNewSource, LPCTSTR strOldSource);
};	
