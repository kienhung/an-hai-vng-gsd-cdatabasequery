#pragma once
#include "launcher.h"

class CAHKLauncher :
	public CLauncher
{
protected:

	CString m_strAHKLauncher;
	CString m_strGameAlias;
	int m_iExtraMinute;
	BOOL m_bResult;

protected:
	BOOL PrepareForAll();
	virtual BOOL BeforeRun();
	virtual BOOL AfterRun();

public:

	CAHKLauncher(LPCTSTR strSource, LPCTSTR strAHKLauncher);
	virtual ~CAHKLauncher(void);
	virtual CString GetName();
	virtual BOOL Run();

	void Clean( PROCESS_INFORMATION &pi );

};
