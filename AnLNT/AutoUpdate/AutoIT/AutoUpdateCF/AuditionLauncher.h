#pragma once
#include "crossfirelauncher.h"

class CAuditionLauncher :
	public CCrossfireLauncher
{
protected:
	HWND m_hMainWnd;
	BOOL m_isMonitoring;

public:
	CAuditionLauncher(LPCTSTR strSourcePath, LPCTSTR strLauncherPath);
	virtual ~CAuditionLauncher(void);
	virtual BOOL Run();
	virtual CString GetName();

	static DWORD WINAPI MonitorThreadFunction(PVOID pvParam);
};
