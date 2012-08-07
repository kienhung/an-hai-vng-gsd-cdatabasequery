#pragma once
#include "autolauncher.h"
#include "CrossfireLauncher.h"

class CFifaLauncher2 :
	public CCrossfireLauncher
{
public:
	CFifaLauncher2(LPCTSTR strSourcePath, LPCTSTR strLauncherPath);
	virtual ~CFifaLauncher2(void);

	virtual CString GetName();
	virtual BOOL Run();
private:

};
