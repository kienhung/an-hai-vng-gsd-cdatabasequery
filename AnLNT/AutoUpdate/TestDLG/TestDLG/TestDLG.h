
// TestDLG.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTestDLGApp:
// See TestDLG.cpp for the implementation of this class
//

class CTestDLGApp : public CWinAppEx
{
public:
	CTestDLGApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTestDLGApp theApp;