#pragma once
#include "autolauncher.h"

class CCrossfireLauncher :
	public CAutoLauncher
{
public:

	CCrossfireLauncher(LPCTSTR strSourcePath, LPCTSTR strLauncherPath);
	virtual ~CCrossfireLauncher(void);

	virtual BOOL Run();
	static BOOL CALLBACK FindSourcePathEditEnumProc(HWND hWnd,LPARAM lParam) ;

protected:
	BOOL SetSourcePath(HWND hMainWnd);

};
