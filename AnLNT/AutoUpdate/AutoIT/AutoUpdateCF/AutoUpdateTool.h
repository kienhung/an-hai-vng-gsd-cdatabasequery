#pragma once
#include "AutoLauncher.h"

class CAutoUpdateTool
{
protected:

	CString m_strSourcePath;
	CString m_strLauncherPath;
	CString m_strToken;
	CString m_strTempSourcePath;

	CAutoLauncher *m_pAutoLauncher;

public:

	CAutoUpdateTool();
	BOOL Create(CAutoLauncher *pAutoLauncher, LPCTSTR strToken);
	BOOL Update();
	virtual ~CAutoUpdateTool(void);
protected:
	BOOL CloneSource();
	BOOL RunAutoLauncher();
	BOOL Compare();
	BOOL RemoveTempSource();
};
