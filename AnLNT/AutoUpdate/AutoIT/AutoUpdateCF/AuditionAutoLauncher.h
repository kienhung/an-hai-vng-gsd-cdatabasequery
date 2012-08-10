#pragma once
#include "launcher.h"

class CAuditionAutoLauncher :
	public CLauncher
{
protected:

	int m_iPanelID;
	int m_iHCMButtonID;
	int m_iGoButtonID;
	int m_iHNButtonID;
	int m_iLoginDialogID;
	int m_iCloseButtonID;

public:
	CAuditionAutoLauncher(LPCTSTR strSource);
	virtual ~CAuditionAutoLauncher(void);

	virtual CString GetName();
	virtual BOOL Run();

	static DWORD WINAPI MonitorThreadFunction(PVOID pvParam);
	static BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam);

};
