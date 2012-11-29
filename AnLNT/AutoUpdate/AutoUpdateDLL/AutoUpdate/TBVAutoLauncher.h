#pragma once
#include "launcherex.h"


class CTBVAutoLauncher :
	public CLauncherEx
{
protected:

	CString m_strRootSource;

	CString m_strBV1WindowClass;
	CString m_strBV1WindowTitle;
	CString m_strBV2WindowClass;
	CString m_strBV2WindowTitle;

	DWORD m_dwTimeOutInMinute;
	void CreateSourceAndLauncherPath(LPCTSTR strGameFolderName, LPCTSTR strGameLauncherName);
	BOOL ReadConfig();
public:
	CTBVAutoLauncher(LPCTSTR strSource);
	virtual ~CTBVAutoLauncher(void);
	virtual CString GetName();
	virtual BOOL Run();
	virtual CGameSourceCompare * GetComparer (LPCTSTR strNewSource, LPCTSTR strOldSource);
	virtual CString GetSourcePath();
};
