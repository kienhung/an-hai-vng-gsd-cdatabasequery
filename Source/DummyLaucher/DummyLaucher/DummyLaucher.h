
// DummyLaucher.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDummyLaucherApp:
// See DummyLaucher.cpp for the implementation of this class
//

class CDummyLaucherApp : public CWinAppEx
{
private:
	BOOL CopyDummyApp(const TCHAR* strPathOldDummy);
public:
	CDummyLaucherApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDummyLaucherApp theApp;