#pragma once
#include "launcher.h"

class CFifa2AutoLauncher :
	public CLauncher
{
protected:
	int iAcceptCheckboxID;
	int iZone1RadioButtonID;
	int iStartButtonID;
public:

	CFifa2AutoLauncher(LPCTSTR strSource);

	virtual BOOL Run();
	virtual CString GetName();
	BOOL WaitForComplete();

	virtual ~CFifa2AutoLauncher(void);
};
