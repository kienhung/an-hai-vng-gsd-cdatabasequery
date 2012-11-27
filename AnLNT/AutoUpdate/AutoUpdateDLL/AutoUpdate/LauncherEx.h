#pragma once
#include "launcher.h"
#include "Include/pugixml.hpp"
using namespace pugi;
using namespace std;

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
	static BOOL WaitForWindowDisappeared(HWND hWnd, DWORD dwTimeout);
protected:
	xml_document m_launcherConfig;
	xml_parse_result m_ConfigLoadingResult;
};
