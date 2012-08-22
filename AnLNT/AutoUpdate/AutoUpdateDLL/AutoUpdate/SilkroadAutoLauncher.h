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

public:
	CSilkroadAutoLauncher(LPCTSTR strSource);
	virtual ~CSilkroadAutoLauncher(void);

	virtual CString GetName();
	virtual BOOL Run();

	BOOL WaitForComplete();
};
