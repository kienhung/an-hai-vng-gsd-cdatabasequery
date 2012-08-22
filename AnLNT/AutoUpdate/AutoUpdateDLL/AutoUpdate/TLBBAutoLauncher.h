#pragma once
#include "launcher.h"

class CTLBBAutoLauncher :
	public CLauncher
{
protected:

	int m_CloseButtonID;

	DWORD m_LoginServerFileLowWriteTime;
	DWORD m_LoginServerFileHighWriteTime;

	int m_iDelayTime;

public:
	CTLBBAutoLauncher(LPCTSTR strSource);

	virtual BOOL Run();
	virtual CString GetName();
	virtual ~CTLBBAutoLauncher(void);

	BOOL GetLoginServerFileWriteTime(DWORD *pLowWriteTime, DWORD *pHighWriteTime);
	BOOL WaitForComplete();
};
