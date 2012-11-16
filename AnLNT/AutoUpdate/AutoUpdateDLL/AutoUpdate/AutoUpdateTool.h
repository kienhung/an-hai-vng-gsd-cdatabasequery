#pragma once


#include "Launcher.h"

class  CAutoUpdateTool
{
protected:

	CString m_strSourcePath;
	CString m_strToken;
	CString m_strTempSourcePath;

	CLauncher *m_pAutoLauncher;
	CString m_strLogFilePath;

public:


	CAutoUpdateTool();
	BOOL Create(CLauncher *pAutoLauncher, LPCTSTR strToken);
	BOOL Create(CLauncher *pAutoLauncher, LPCTSTR strToken, LPCTSTR strCCSource);
	BOOL Update();
	CString GetName();

	virtual ~CAutoUpdateTool(void);
protected:
	BOOL CloneSource();
	BOOL RunAutoLauncher();
	BOOL Compare();
	BOOL RemoveTempSource();
	void WriteDebugLog(const CString &strLog);
	void WriteErrorLog(const CString &strLog);
};
