#pragma once
#include "autolauncher.h"

class CCrossfireLauncher :
	public CAutoLauncher
{
public:

	CCrossfireLauncher(LPCTSTR strSourcePath, LPCTSTR strLauncherPath);

	virtual ~CCrossfireLauncher(void);
	virtual BOOL Run();

	BOOL PressTiepTheoButton( HWND hMainWnd );

	//static BOOL CALLBACK FindTiepTheoButtonEnumProc(HWND hWnd,LPARAM lParam) ;
	static BOOL CALLBACK FindSourcePathEditEnumProc(HWND hWnd,LPARAM lParam) ;

protected:
	HWND StartCrossfireLauncher();
	BOOL SetSourcePath(HWND hMainWnd);
};
