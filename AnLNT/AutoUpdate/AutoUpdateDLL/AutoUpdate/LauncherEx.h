#pragma once
#include "launcher.h"

class CLauncherEx :
	public CLauncher
{
public:
	CLauncherEx(LPCTSTR strSource);
	virtual ~CLauncherEx(void);
protected:
	PROCESS_INFORMATION m_processInfo;
	virtual BOOL StartLauncherProcess();
	virtual HWND StartLauncherWindow(LPCTSTR strClassName, LPCTSTR strWindowName);
	static BOOL IsWindowShowed(HWND hWnd);
	static HWND WaitForWindow(LPCTSTR strClassName, LPCTSTR strWindowName, DWORD dwTimeout);
	static HWND WaitForWindow(LPCTSTR strClassName, LPCTSTR strWindowName, DWORD dwTimeout, DWORD dwLoop);
};
