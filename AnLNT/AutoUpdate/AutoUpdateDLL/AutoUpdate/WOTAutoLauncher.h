#pragma once
#include "launcher.h"

class CWOTAutoLauncher :
	public CLauncher
{
protected:

	HANDLE m_hProcess;
	FILETIME m_ftConfigFileLastWriteTime;
	CString m_strConfigFilePath;
	CString m_strLogFilePath;

	int m_iDelayTime;

public:
	CWOTAutoLauncher(LPCTSTR strSource);
	virtual ~CWOTAutoLauncher(void);

	virtual CString GetName();
	virtual BOOL Run();
	virtual BOOL Compare(LPCTSTR strSourcePath, LPCTSTR strTempSourcePath);
protected:
	
	virtual BOOL StartLauncherProcess();
	BOOL GetConfigFileLastWriteTime();
	BOOL WaitForUpdateBeginning();
	BOOL WaitForComplate();

	BOOL ProcessError();
	BOOL KillProcess();
	BOOL ProcessComplete();
};
