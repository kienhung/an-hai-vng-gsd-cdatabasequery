#pragma once
#include "launcher.h"

class CCrossfireAutoLauncher :
	public CLauncher
{
protected:
	int m_iStartButtonID;
	BOOL WaitForComplete();
public:
	CCrossfireAutoLauncher(LPCTSTR strSource);
	virtual ~CCrossfireAutoLauncher(void);

	virtual CString GetName();
	virtual BOOL Run();
};
