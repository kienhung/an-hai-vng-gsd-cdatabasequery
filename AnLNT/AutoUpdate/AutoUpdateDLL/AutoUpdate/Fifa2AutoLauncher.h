#pragma once
#include "launcher.h"

class CFifa2AutoLauncher :
	public CLauncher
{
protected:
	int m_iAcceptCheckboxID;
	int m_iZone1RadioButtonID;
	int m_iStartButtonID;

	int m_iFailedOkButtonID;

	CString m_strWindowName;
	CString m_strClassName;

	enum STATE {CONNECT, DISCONNECT, UNKNOWN};
	STATE m_state;
public:

	CFifa2AutoLauncher(LPCTSTR strSource);

	virtual BOOL Run();
	virtual CString GetName();
	

	virtual ~CFifa2AutoLauncher(void);

	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam );
	static BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam );

protected:
	BOOL WaitForComplete();
	HWND StartLauncherWindow();
	//BOOL KillMainWindowProcess();
};
