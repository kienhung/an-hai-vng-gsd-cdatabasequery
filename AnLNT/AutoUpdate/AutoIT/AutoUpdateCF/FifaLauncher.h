#pragma once
#include "autolauncher.h"
#include "CrossfireLauncher.h"

class CFifaLauncher :
	public CCrossfireLauncher
{
public:
	CFifaLauncher(LPCTSTR strSourcePath, LPCTSTR strLauncherPath);
	virtual ~CFifaLauncher(void);

	virtual BOOL Run();
private:

};
